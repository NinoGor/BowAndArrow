#include "Surface.h"
#include "ChiliWin.h"
#include <cassert>
#include <fstream>

Surface::Surface(const std::string& filename)
{
	std::ifstream file(filename, std::ios::binary);
	assert(file);

	BITMAPFILEHEADER bmFileH;
	file.read(reinterpret_cast<char*>(&bmFileH), sizeof(bmFileH));

	BITMAPINFOHEADER bmInfoH;
	file.read(reinterpret_cast<char*>(&bmInfoH), sizeof(bmInfoH));

	assert(bmInfoH.biBitCount == 24 || bmInfoH.biBitCount == 32);
	assert(bmInfoH.biCompression == BI_RGB);

	const bool is32b = bmInfoH.biBitCount == 32;

	width = bmInfoH.biWidth;
	int yStart;
	int yStop;

	if (bmInfoH.biHeight < 0)
	{
		height = -bmInfoH.biHeight;
		pPixels = new Color[width * height];
		yStop = height;
		yStart = 0;
	}
	else
	{
		height = bmInfoH.biHeight;
		pPixels = new Color[width * height];
		yStop = 0;
		yStart = height - 1;
	}

	file.seekg(bmFileH.bfOffBits);
	const int padding = (4 - (width * 3) % 4) % 4;

	for (int y = yStart; y != yStop; y--)
	{
		for (int x = 0; x < width; x++)
		{
			PutPixel(x, y, Color(file.get(), file.get(), file.get()));
			if (is32b)
			{
				file.seekg(1, std::ios::cur);
			}
		}
		if (!is32b)
		{
			file.seekg(padding, std::ios::cur);
		}
		if (bmInfoH.biHeight < 0)
		{
			y += 2;
		}
	}

}

Surface::Surface(int width, int height)
	:
	width(width),
	height(height),
	pPixels(new Color[width * height])
{
}

Surface::Surface(const Surface& rhs)
	:
	Surface(rhs.width, rhs.height)
{
	const int nPixels = width * height;
	for (int i = 0; i < nPixels; i++)
	{
		pPixels[i] = rhs.pPixels[i];
	}
}

Surface::~Surface()
{
	delete[] pPixels;
	pPixels = nullptr;
}

Surface& Surface::operator=(const Surface& rhs)
{
	delete[] pPixels;
	pPixels = new Color[rhs.width * rhs.height];

	const int nPixels = rhs.width * rhs.height;
	for (int i = 0; i < nPixels; i++)
	{
		pPixels[i] = rhs.pPixels[i];
	}
	return *this;
}

void Surface::PutPixel(int x, int y, Color c)
{
	assert(x >= 0);
	assert(x < width);
	assert(y >= 0);
	assert(y < height);
	pPixels[y * width + x] = c;
}

Color Surface::GetPixel(int x, int y) const
{
	assert(x >= 0);
	assert(x < width);
	assert(y >= 0);
	assert(y < height);
	return pPixels[y * width + x];
}

int Surface::GetWidth() const
{
	return width;
}

int Surface::GetHeight() const
{
	return height;
}

RectI Surface::GetRect() const
{
	return{0,width,0,height};
}
