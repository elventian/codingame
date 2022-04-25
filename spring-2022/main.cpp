#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <math.h>

using namespace std;

int main(int argc, char **argv)
{
	if (argc > 2) {
		cerr << "Usage:\n\t" << argv[0] << "\n\t" << argv[0] << " <input_file>\n";
		exit(1);
	}
	
	ifstream infile;
	if (argc == 2) {
		infile.open(argv[1]);
		if (!infile.is_open()) {
			cerr << "Can't open file \"" << argv[1] << "\" for reading\n";
			exit(1);
		}
	}
	istream &in = (argc == 2)? infile : cin;
	
	int base_x; // The corner of the map representing your base
	int base_y;
	in >> base_x >> base_y; in.ignore();
	std::cerr << base_x << " " << base_y << std::endl;
	int opbase_x = 17630 - base_x;
	int opbase_y = 9000 - base_y;
	int heroes_per_player; // Always 3
	in >> heroes_per_player; in.ignore();
	std::cerr << heroes_per_player << std::endl;
	
	int my_mana = 0;
	// game loop
	while (1) {
		for (int i = 0; i < 2; i++) {
			int health; // Your base health
			int mana; // Ignore in the first league; Spend ten mana to cast a spell
			in >> health >> mana; in.ignore();
			std::cerr << health << " " << mana << std::endl;
			if (i == 0) { my_mana = mana; }
		}
		int entity_count; // Amount of heros and monsters you can see
		in >> entity_count; in.ignore();
		std::cerr << entity_count << std::endl;
		list<pair<int,int>> bugs;
		vector<pair<int,int>> heroes;
		for (int i = 0; i < entity_count; i++) {
			int id; // Unique identifier
			int type; // 0=monster, 1=your hero, 2=opponent hero
			int x; // Position of this entity
			int y;
			int shield_life; // Ignore for this league; Count down until shield spell fades
			int is_controlled; // Ignore for this league; Equals 1 when this entity is under a control spell
			int health; // Remaining health of this monster
			int vx; // Trajectory of this monster
			int vy;
			int near_base; // 0=monster with no target yet, 1=monster targeting a base
			int threat_for; // Given this monster's trajectory, is it a threat to 1=your base, 2=your opponent's base, 0=neither
			in >> id >> type >> x >> y >> shield_life >> is_controlled >> health >> vx >> vy >> near_base >> threat_for; in.ignore();
			std::cerr << id << " " << type << " " <<  x  << " " << y << " " << shield_life << " " << 
				is_controlled << " " << health << " " << vx << " " << vy << " " << near_base << " " << 
				threat_for << std::endl;
			if (type == 0 && near_base && threat_for == 1) {
				bugs.push_back(pair<int,int>(x, y));
			}
			if (type == 1) {
				heroes.push_back(pair<int,int>(x, y));
			}
		}
		bugs.sort([base_x, base_y](const pair<int,int> &p1, const pair<int,int> &p2) {
			return abs(base_x - p1.first) + abs(base_y - p1.second) < 
			abs(base_x - p2.first) + abs(base_y - p2.second);
		});
		for (int i = 0; i < heroes_per_player; i++) {
			
			// Write an action using cout. DON'T FORGET THE "<< endl"
			// To debug: cerr << "Debug messages..." << endl;
			
			
			// In the first league: MOVE <x> <y> | WAIT; In later leagues: | SPELL <spellParams>;
			bool action_done = false;
			if (bugs.empty()) { cout << "WAIT" << endl; action_done = true; }
			else if (my_mana >= 10) {
				for (pair<int,int>bug: bugs) {
					int dx = heroes[i].first - bug.first;
					int dy = heroes[i].second - bug.second;
					int dist = sqrt(dx * dx + dy * dy);
					if (dist <= 1280) {
						cout << "SPELL WIND " << opbase_x << " " << opbase_y << endl;
						my_mana -= 10;
						action_done = true;
						break;
					}
				}
			}
			if (!action_done) { 
				cout << "MOVE " << bugs.front().first << " " << bugs.front().second << endl;
				bugs.erase(bugs.begin());
				action_done = true;
			}
		}
		if (argc == 2) { exit(0); }
	}
	
	return 0;
}

