#include "Phys.h"

namespace phys
{
	double kg()
	{
		return 1.0;
	}
	double g()
	{
		return 1e-3 * kg();
	}
	double Da()
	{
		return 1.66e-27 * kg();
	}

	double m()
	{
		return 1.0;
	}
	double cm()
	{
		return 1e-2 * m();
	}
	double mm()
	{
		return 1e-3 * m();
	}
	double um()
	{
		return 1e-6 * m();
	}
	double angstrem()
	{
		return 1e-10 * m();
	}

	double barn()
	{
		return 1e-28 * pow(m(), 2.0);
	}

	double s()
	{
		return 1.0;
	}
	double ms()
	{
		return 1e-3 * s();
	}

	double J()
	{
		return 1.0;
	}
	double eV()
	{
		return 1.6e-19 * J();
	}
	double KeV()
	{
		return 1e3 * eV();
	}
	double MeV()
	{
		return 1e6 * eV();
	}

	double K()
	{
		return 1.0;
	}

	double stefanBoltzmanConstant()
	{
		return 5.670374419 * 1e-8 * J() / s() / pow(m(), 2.0) / pow(K(), 4.0);
	}
}