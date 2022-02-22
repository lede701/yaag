#ifndef H_CONCOLOR
#define H_CONCOLOR

namespace Zaxis{ namespace Graphics{ namespace ConGraphicsData
{

	enum ConColor
	{
		Black = 0x0000,
		Blue = 0x0001,
		Green = 0x0002,
		Red = 0x0004,
		Intensity = 0x0008,
		LtBlue = Blue | Intensity,
		LtGreen = Green | Intensity,
		LtRed = Red | Intensity,
		Torquoise = Blue | Green,
		LtTorquoise = Torquoise | Intensity,
		Purple = Red | Blue,
		LtPurple = Purple | Intensity,
		Yellow = Green | Red,
		LtYellow = Yellow | Intensity,
		Grey = Blue | Green | Red,
		White = Grey | Intensity,

		BkgBlue = 0x0010,
		BkgGreen = 0x0020,
		BkgRed = 0x0040,
		BkgIntensity = 0x0080,
		BkgLtBlue = BkgBlue | BkgIntensity,
		BkgLtGreen = BkgGreen | BkgIntensity,
		BkgLtRed = BkgRed | BkgIntensity,
		BkgTorquoise = BkgBlue | BkgGreen,
		BkgLtTorquoise = BkgTorquoise | BkgIntensity,
		BkgPurple = BkgRed | BkgBlue,
		BkgLtPutple = BkgPurple | BkgIntensity,
		BkgYellow = BkgRed | BkgGreen,
		BkgLtYellow = BkgYellow | BkgIntensity,
		BkgGrey = BkgRed | BkgGreen | BkgBlue,
		BkgWhite = BkgGrey | BkgIntensity
	};

} } }// End namespace Zaxis::Graphics::ConGraphicsData

#endif