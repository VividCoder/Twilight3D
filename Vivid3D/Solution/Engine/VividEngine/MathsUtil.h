#pragma once



namespace Vivid {

	namespace Maths {

		const double PI = 3.1415926535897932384626433832795028841971693993751058209;

		class MathsUtil
		{
		public:

			static float DegToRad(float deg) {

				return (deg * PI) / 180.0f;

			};

			static float RadToDeg(float rad) {

				return (rad * 180) / PI;

			}

		};

	}

}
