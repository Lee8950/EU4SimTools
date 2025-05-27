#include <siege.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <algorithm>
#include <random>
#include <cstring>

bool SiegePossible(std::shared_ptr<ecl::SiegeSimulation> siege)
{
    return true;
    //int maxPoint = 0;
    //maxPoint = 14 - siege->defender_fort_level + siege->attacker_leader_siege_ability + siege->attacker_fort_blockade;
}

double ArtilleryBonus(std::shared_ptr<ecl::SiegeSimulation> siege)
{
    switch(siege->defender_fort_level) {
    case 1:{
        if(siege->attacker_napoleon_tactics && siege->attacker_artillery_amount>=8000)return 8.0;
        if(siege->attacker_napoleon_tactics && siege->attacker_artillery_amount>=7000)return 7.0;
        if(siege->attacker_napoleon_tactics && siege->attacker_artillery_amount>=6000)return 6.0;
        if(siege->attacker_artillery_amount>=5000)return 5.0;
        if(siege->attacker_artillery_amount>=4000)return 4.0;
        if(siege->attacker_artillery_amount>=3000)return 3.0;
        if(siege->attacker_artillery_amount>=2000)return 2.0;
        if(siege->attacker_artillery_amount>=1000)return 1.0;
        return 0.0;
    }
    case 2:{
        if(siege->attacker_napoleon_tactics && siege->attacker_artillery_amount>=16000)return 8.0;
        if(siege->attacker_napoleon_tactics && siege->attacker_artillery_amount>=14000)return 7.0;
        if(siege->attacker_napoleon_tactics && siege->attacker_artillery_amount>=12000)return 6.0;
        if(siege->attacker_artillery_amount>=10000)return 5.0;
        if(siege->attacker_artillery_amount>=8000)return 4.0;
        if(siege->attacker_artillery_amount>=6000)return 3.0;
        if(siege->attacker_artillery_amount>=4000)return 2.0;
        if(siege->attacker_artillery_amount>=1000)return 1.0;
        return 0.0;
    }
    case 4:{
        if(siege->attacker_napoleon_tactics && siege->attacker_artillery_amount>=24000)return 8.0;
        if(siege->attacker_napoleon_tactics && siege->attacker_artillery_amount>=21000)return 7.0;
        if(siege->attacker_napoleon_tactics && siege->attacker_artillery_amount>=18000)return 6.0;
        if(siege->attacker_artillery_amount>=15000)return 5.0;
        if(siege->attacker_artillery_amount>=12000)return 4.0;
        if(siege->attacker_artillery_amount>=9000)return 3.0;
        if(siege->attacker_artillery_amount>=6000)return 2.0;
        if(siege->attacker_artillery_amount>=1000)return 1.0;
        return 0.0;
    }
    case 6:{
        if(siege->attacker_napoleon_tactics && siege->attacker_artillery_amount>=32000)return 8.0;
        if(siege->attacker_napoleon_tactics && siege->attacker_artillery_amount>=28000)return 7.0;
        if(siege->attacker_napoleon_tactics && siege->attacker_artillery_amount>=24000)return 6.0;
        if(siege->attacker_artillery_amount>=20000)return 5.0;
        if(siege->attacker_artillery_amount>=16000)return 4.0;
        if(siege->attacker_artillery_amount>=12000)return 3.0;
        if(siege->attacker_artillery_amount>=8000)return 2.0;
        if(siege->attacker_artillery_amount>=1000)return 1.0;
        return 0.0;
    }
    case 8:{
        if(siege->attacker_napoleon_tactics && siege->attacker_artillery_amount>=40000)return 8.0;
        if(siege->attacker_napoleon_tactics && siege->attacker_artillery_amount>=35000)return 7.0;
        if(siege->attacker_napoleon_tactics && siege->attacker_artillery_amount>=30000)return 6.0;
        if(siege->attacker_artillery_amount>=25000)return 5.0;
        if(siege->attacker_artillery_amount>=20000)return 4.0;
        if(siege->attacker_artillery_amount>=15000)return 3.0;
        if(siege->attacker_artillery_amount>=10000)return 2.0;
        if(siege->attacker_artillery_amount>=1000)return 1.0;
        return 0.0;
    }
    }
    return 0.0;
}

double OutdatedFortBonus(std::shared_ptr<ecl::SiegeSimulation> siege)
{
    if(siege->attacker_fort_max_level>siege->defender_fort_level)
        return siege->attacker_fort_max_level-siege->defender_fort_level;
    return 0.0;
}

void init(std::shared_ptr<ecl::SiegeSimulation> siege)
{
    siege->accumulate_siege_time = 0;
    siege->accumulate_siege_bonus = 0;
    siege->attacker_accumulate_casualties = 0;
    siege->wall_breached = 0;
    siege->basic_attrition = 0.01;
}

int main(int argc, char **argv)
{
    std::shared_ptr<ecl::SiegeSimulation> siege_start_setup = std::make_shared<ecl::SiegeSimulation>();
    std::shared_ptr<ecl::SiegeSimulation> siege_sim;
    //double artillery_bonus = ArtilleryBonus(siege_sim);
    init(siege_start_setup);

    siege_start_setup->attacker_siege_ability = 0.82;
    siege_start_setup->attacker_military_tactics = 1.5;
    siege_start_setup->attacker_leader_siege_ability = 1;
    siege_start_setup->attacker_artillery_amount = 8000;
    siege_start_setup->attacker_siege_manpower = 25000;
    siege_start_setup->attacker_fort_max_level = 8;
    siege_start_setup->attacker_fort_blockade = -2;
    siege_start_setup->attacker_napoleon_tactics = false;

    siege_start_setup->defender_fort_defense = 1.25;
    siege_start_setup->defender_military_tactics = 1.25;
    siege_start_setup->defender_fort_level = 6;
    siege_start_setup->defender_fort_max_manpower = 8000;
    siege_start_setup->defender_fort_manpower = 8000;

    uint32_t received_parameters = 0x00000000;
    uint32_t sufficient_parameters = 0x00001FFF;

    for(int i = 0; i < argc;)
    {
        if(strcmp("--attacker_siege_ability", argv[i])==0) {
            siege_start_setup->attacker_siege_ability = std::stod(argv[++i]);
            i++;
            received_parameters |= 0x00000001;
            continue;
            //std::cout << "-k" << std::endl;
        }
        else if(strcmp("--attacker_military_tactics", argv[i])==0) {
            siege_start_setup->attacker_military_tactics = std::stod(argv[++i]);
            i++;
            received_parameters |= 0x00000002;
            continue;
        }
        else if(strcmp("--attacker_leader_siege_ability", argv[i])==0) {
            siege_start_setup->attacker_leader_siege_ability = std::stoi(argv[++i]);
            i++;
            received_parameters |= 0x00000004;
            continue;
        }
        else if(strcmp("--attacker_artillery_amount", argv[i])==0) {
            siege_start_setup->attacker_artillery_amount = std::stoi(argv[++i]);
            i++;
            received_parameters |= 0x00000008;
            continue;
        }
        else if(strcmp("--attacker_siege_manpower", argv[i])==0) {
            siege_start_setup->attacker_siege_manpower = std::stoi(argv[++i]);
            i++;
            received_parameters |= 0x00000010;
            continue;
        }
        else if(strcmp("--attacker_fort_max_level", argv[i])==0) {
            siege_start_setup->attacker_fort_max_level = std::stoi(argv[++i]);
            i++;
            received_parameters |= 0x00000020;
            continue;
        }
        else if(strcmp("--attacker_fort_blockade", argv[i])==0) {
            siege_start_setup->attacker_fort_blockade = std::stoi(argv[++i]);
            i++;
            received_parameters |= 0x00000040;
            continue;
        }
        else if(strcmp("--attacker_napoleon_tactics", argv[i])==0) {
            if(strcmp(argv[i+1], "true")==0)
                siege_start_setup->attacker_napoleon_tactics = true;
            if(strcmp(argv[i+1], "false")==0)
                siege_start_setup->attacker_napoleon_tactics = false;
            if(strcmp(argv[i+1], "1")==0)
                siege_start_setup->attacker_napoleon_tactics = true;
            if(strcmp(argv[i+1], "0")==0)
                siege_start_setup->attacker_napoleon_tactics = false;
            i+=2;
            received_parameters |= 0x00000080;
            continue;
        }
        else if(strcmp("--defender_fort_defense", argv[i])==0) {
            siege_start_setup->defender_fort_defense = std::stoi(argv[++i]);
            i++;
            received_parameters |= 0x00000100;
            continue;
        }
        else if(strcmp("--defender_military_tactics", argv[i])==0) {
            siege_start_setup->defender_military_tactics = std::stod(argv[++i]);
            i++;
            received_parameters |= 0x00000200;
            continue;
        }
        else if(strcmp("--defender_fort_level", argv[i])==0) {
            siege_start_setup->defender_fort_level = std::stoi(argv[++i]);
            i++;
            received_parameters |= 0x00000400;
            continue;
        }
        else if(strcmp("--defender_fort_max_manpower", argv[i])==0) {
            siege_start_setup->defender_fort_max_manpower = std::stoi(argv[++i]);
            i++;
            received_parameters |= 0x00000800;
            continue;
        }
        else if(strcmp("--defender_fort_manpower", argv[i])==0) {
            siege_start_setup->defender_fort_manpower = std::stoi(argv[++i]);
            i++;
            received_parameters |= 0x00001000;
            continue;
        }
        else if(strcmp("-h", argv[i])==0)
        {
            break;
        }
        else {
#ifdef DEBUG
            std::cout << "failed to match:"+std::string(argv[i])+" at "+std::to_string(i) << std::endl;
#endif
        }
        i++;
    }
    //std::cout << received_parameters << " " << sufficient_parameters << std::endl;
    if((received_parameters & sufficient_parameters) != sufficient_parameters)
    {
        printf("Usage: %s --attacker_siege_ability [double] --attacker_military_tactics [double] --attacker_leader_siege_ability [int] \
--attacker_artillery_amount [int] --attacker_siege_manpower [int] --attacker_fort_max_level [int] --attacker_fort_blockade [int] \
--attacker_napoleon_tactics [true|false|1|0] --defender_fort_defense [double] --defender_military_tactics [double] \
--defender_fort_level [int] --defender_fort_max_manpower [int] --defender_fort_manpower [int]", argv[0]);
        return 0;
    }

    int dice = 0;

    std::random_device rd;
    std::uniform_int_distribution<int> uniform_distribution(1, 14);
    std::mt19937 engine(rd());

    //std::cout << uniform_distribution(engine) << std::endl;
    siege_sim = std::make_shared<ecl::SiegeSimulation>(*siege_start_setup);
    while(true)
    {
        int siege_time = 30 * 
            (1 - siege_sim->attacker_siege_ability + siege_sim->defender_fort_defense
            + 0.25 * (siege_sim->defender_military_tactics - siege_sim->attacker_military_tactics));

        siege_sim->accumulate_siege_time += siege_time;
        dice = uniform_distribution(engine);

        // pandemic
        if(dice == 1)
        {
            siege_sim->attacker_accumulate_casualties += siege_sim->attacker_siege_manpower * 0.05;
        }
        siege_sim->attacker_accumulate_casualties += siege_sim->attacker_siege_manpower * siege_sim->basic_attrition;
        
        int wall_breached_point = dice + (ArtilleryBonus(siege_sim)+OutdatedFortBonus(siege_sim))/3.0 + siege_sim->attacker_fort_max_level/10.0;
        int sufficient_defender = (siege_sim->defender_fort_manpower>siege_sim->defender_fort_max_manpower*0.5)?
            1 : 0;
        int siege_point_stage = dice
            - siege_sim->defender_fort_level
            + siege_sim->accumulate_siege_bonus
            + siege_sim->attacker_leader_siege_ability
            + siege_sim->attacker_fort_blockade
            + siege_sim->wall_breached;
            + sufficient_defender;
        if(wall_breached_point >= 14)
        {
            if(siege_point_stage >= 20){
                std::cout << "Surrender!!" << std::endl;
                break;
            }
            siege_sim->wall_breached = std::min(siege_sim->wall_breached+1, 3);
            siege_sim->accumulate_siege_bonus += 2;
        }
        else
        {
            // Surrender!!!
            if(siege_point_stage >= 20){
                std::cout << "Surrender!!" << std::endl;
                break;
            }
            else if(siege_point_stage >= 16) {
                std::cout << "Defender escape" << std::endl;
                siege_sim->accumulate_siege_bonus += 2;
                siege_sim->defender_fort_manpower - siege_sim->defender_fort_max_manpower * 0.1;
                // Defender escape
            }
            else if(siege_point_stage >= 14) {
                std::cout << "Water Shortage" << std::endl;
                siege_sim->accumulate_siege_bonus += 2;
                siege_sim->defender_fort_manpower - siege_sim->defender_fort_max_manpower * 0.05;
                // Water Shortage
            }
            else if(siege_point_stage >= 12) {
                std::cout << "Food Shortage" << std::endl;
                siege_sim->accumulate_siege_bonus += 2;
                siege_sim->defender_fort_manpower - siege_sim->defender_fort_max_manpower * 0.03;
                // Food Shortage
            }
            else if(siege_point_stage >= 5) {
                std::cout << "Supplies Shortage" << std::endl;
                siege_sim->accumulate_siege_bonus += 2;
                siege_sim->defender_fort_manpower - siege_sim->defender_fort_max_manpower * 0.01;
                // Supplies Shortage
            }
            else {
                std::cout << "Status Quo" << std::endl;
                // Status Quo
            }
        }
        // Got it
        if(siege_sim->defender_fort_manpower < 100) {
            std::cout << "Insufficient defenders!" << std::endl;
            break;
        }
        
        
    }
    printf("Siege Completed in %d days, with %d casualties.", siege_sim->accumulate_siege_time, siege_sim->attacker_accumulate_casualties);

    return 0;
}