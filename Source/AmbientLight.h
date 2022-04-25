#pragma once
class AmbientLight
{
public:
	AmbientLight();
	AmbientLight(int red, int green, int blue);
	void SetRed(int value);
	int GetRed() const;
	void SetGreen(int value);
	int GetGreen() const;
	void SetBlue(int value);
	int GetBlue() const;
private:
	int _R;
	int _G;
	int _B;
};

