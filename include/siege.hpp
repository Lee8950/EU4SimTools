#pragma once

namespace ecl {

struct SiegeSimulation {

    double basic_attrition;

    double attacker_siege_ability;
    double attacker_military_tactics;

    int attacker_leader_siege_ability;
    int attacker_artillery_amount;

    int attacker_siege_init_manpower;
    int attacker_siege_manpower;

    int attacker_fort_max_level;

    int attacker_fort_blockade;
    bool attacker_napoleon_tactics;

    double attacker_artillery_levels_contribution_to_siege;

    double defender_fort_defense;
    double defender_military_tactics;

    int defender_fort_level;

    int defender_fort_max_level;

    int defender_fort_max_manpower;
    int defender_fort_manpower;


    int accumulate_siege_time = 0;
    int accumulate_siege_bonus = 0;

    int attacker_accumulate_casualties = 0;

    int wall_breached = 0;
};



}