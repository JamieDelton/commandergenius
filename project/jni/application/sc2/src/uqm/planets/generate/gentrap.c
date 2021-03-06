//Copyright Paul Reiche, Fred Ford. 1992-2002

/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include "genall.h"
#include "../planets.h"


static bool GenerateTrap_generatePlanets (SOLARSYS_STATE *solarSys);
static bool GenerateTrap_generateOrbital (SOLARSYS_STATE *solarSys,
		PLANET_DESC *world);


const GenerateFunctions generateTrapFunctions = {
	/* .initNpcs         = */ GenerateDefault_initNpcs,
	/* .reinitNpcs       = */ GenerateDefault_reinitNpcs,
	/* .uninitNpcs       = */ GenerateDefault_uninitNpcs,
	/* .generatePlanets  = */ GenerateTrap_generatePlanets,
	/* .generateMoons    = */ GenerateDefault_generateMoons,
	/* .generateName     = */ GenerateDefault_generateName,
	/* .generateOrbital  = */ GenerateTrap_generateOrbital,
	/* .generateMinerals = */ GenerateDefault_generateMinerals,
	/* .generateEnergy   = */ GenerateDefault_generateEnergy,
	/* .generateLife     = */ GenerateDefault_generateLife,
};


static bool
GenerateTrap_generatePlanets (SOLARSYS_STATE *solarSys)
{
	COUNT angle;

	GenerateDefault_generatePlanets (solarSys);

	solarSys->PlanetDesc[0].data_index = TELLURIC_WORLD;
	solarSys->PlanetDesc[0].NumPlanets = 1;
	solarSys->PlanetDesc[0].radius = EARTH_RADIUS * 203L / 100;
	angle = ARCTAN (solarSys->PlanetDesc[0].location.x,
			solarSys->PlanetDesc[0].location.y);
	solarSys->PlanetDesc[0].location.x =
			COSINE (angle, solarSys->PlanetDesc[0].radius);
	solarSys->PlanetDesc[0].location.y =
			SINE (angle, solarSys->PlanetDesc[0].radius);

	return true;
}

static bool
GenerateTrap_generateOrbital (SOLARSYS_STATE *solarSys, PLANET_DESC *world)
{
	GenerateDefault_generateOrbital (solarSys, world);

	if (matchWorld (solarSys, world, 0, MATCH_PLANET))
	{
		solarSys->SysInfo.PlanetInfo.AtmoDensity = EARTH_ATMOSPHERE * 2;
		solarSys->SysInfo.PlanetInfo.SurfaceTemperature = 35;
		solarSys->SysInfo.PlanetInfo.Weather = 3;
		solarSys->SysInfo.PlanetInfo.Tectonics = 1;
	}

	return true;
}

