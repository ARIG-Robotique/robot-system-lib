/*
 * Convertion.h
 *
 *  Created on: 24 déc. 2012
 *      Author: mythril
 */

#ifndef CONVERTION_H_
#define CONVERTION_H_

namespace utils {

	#define COUNT_PER_MM				4.044	 			// Nombre d'impulsion codeur pour 1mm
	#define COUNT_PER_DEG				11.36 				// 5.68 * 2 Nombre de count pour réalisé 1°
	#define COUNT_PER_RAD				325.542 * 2			// Nombre de count pour réalisé 1 radian

	class Convertion {
	public:
		Convertion();
		virtual ~Convertion();

		long int mmToPulse(long int);
		long int pulseToMm(long int);
		long int degToPulse(long double);
		long double pulseToDeg(long int);
		long double pulseToRad(long int);
		long int radToPulse(long double);
	};

} /* namespace utils */
#endif /* CONVERTION_H_ */
