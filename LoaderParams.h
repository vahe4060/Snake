#pragma once

class loaderParams {
	int X, Y;
	int Height, Width;
	const char* ID;
public:
	loaderParams(int x_, int y_, int width_, int height_, const char* id_) :
		X(x_),
		Y(y_),
		Width(width_),
		Height(height_),
		ID(id_)
	{

	}

	~loaderParams() {}
	int x() const {	return X; }
	int y() const { return Y; }
	int width() const { return Width; }
	int height() const { return Height; }
	const char* id() const { return ID; }
};