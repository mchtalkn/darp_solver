#include <iostream>
#include "DarpSolverBF.h"
#include "DarpSolverHAC.h"
#include <math.h>
#include <fstream>
#include <Helpers.h>
#include "Kmeans.h"
#include "DarpSolverKmeans.h"
using namespace std;
template <class t>
t& set_reference(t& lhs, t& rhs,bool assign_left ) {
	if (assign_left) return lhs;
	return rhs;
}

int main(int argc, char** argv) {
	string clustering[3] = {"single","complete","average"};
	string distances[3] = { "min_sg","max_sg","middle" };
	ifstream in_file;
	ofstream o_file;
	bool in_from_file = false;
	bool out_from_file = false;
	bool brute_active = false;
	int number_of_scenarios = 1;
	bool print_header = true;
	if (argc > 7 || argc == 3) {
		cerr << "argument count doesnt match" << endl << flush;
		exit(-1);

	}
	if (argc >= 7) {
		string s = argv[6];
		if (s == "y") {
			brute_active = true;
		}
		else if (s == "n") {
			brute_active = false;
		}
		else {
			cerr << "brute active argument couldnt recognized"<<endl;
			exit(-1);
		}
	}
	if (argc >= 6) {
		string s = argv[5];
		if (s == "y") {
			print_header = true;
		}
		else if (s == "n") {
			print_header = false;
		}
		else {
			cerr << "print_header argument couldnt recognized" << endl;
			exit(-1);
		}
	}
	if (argc >= 5) {
		number_of_scenarios = stoi(argv[4]);
	}
	if (argc >= 4) {
		string mode_s = argv[3];
		std::ios_base::openmode mode;
		if (mode_s == "a") {
			mode = std::ios_base::app;
		}
		else if (mode_s == "o") {
			mode = std::ios_base::out;
		}
		else {
			cerr << "open mode couldnt recognized " << endl;
			exit(-1);
		}
		o_file.open(argv[2], mode);
		out_from_file = true;
	}
	if (argc >= 2) {
		in_file.open(argv[1]);
		in_from_file = true;
	}

	istream& in_stream = set_reference((istream&)in_file, cin, in_from_file);
	ostream& out_stream = set_reference((ostream&)o_file, cout, out_from_file);
	Graph g(in_stream);
	int count = 0;
	if (brute_active) {
		cout << "Brute,,,,";
		count++;
	}
	for (const string& p : RoutePlanner::route_planners) {
		if (!brute_active && p == "brute") continue;
		for (const string& c : HAC::linkages) {
			for (const string& d : HAC::entity_distances) {
				cout << "HAC " << p << " " << c << " " << d << ",,,,";
				count++;
			}
		}
		for (const string& ci : Kmeans::center_initializers) {
			for (const string& ca : Kmeans::center_assignments) {
				for (const string& ecd : Kmeans::entity_center_distances) {
					cout << "Kmeans " << p << " " << ci << " " << ca << " " << ecd << ",,,,";
					count++;
				}
			}
		}
	}
	cout << endl << ",";
	if (print_header) {
		out_stream << "scenario id,";
		for (int i = 0; i < count; i++) {
			out_stream << "total cost " << i << ",max cost " << i << ", assginment time " << i << ", solution time " << i << ",";
		}
		out_stream << endl;
	}
	for (int scenario_number = 0; scenario_number < number_of_scenarios; scenario_number++) {
		vector<task> tasks = readTasksFromFile(in_stream);
		vector<int> agentNodeIds = readAgentNodesFromFile(in_stream);
		vector<route> r1;
		float total_cost = 0;
		float max_cost = 0;
		
		out_stream << scenario_number << ",";
		if (brute_active) {
			DarpSolverBF dsbf(tasks, agentNodeIds, g);
			dsbf.solve();
			r1 = dsbf.getRoutes();

			for (auto& r : r1) {
				total_cost += r.cost;
				max_cost = max(max_cost, r.cost);
			}
			out_stream << total_cost << "," << max_cost << "," << dsbf.assignment_time << "," << dsbf.solution_time << ",";

		}
		for (const string& p : RoutePlanner::route_planners) {
			if (!brute_active && p == "brute") continue;
			for (const string& c : HAC::linkages) {
				for (const string& d : HAC::entity_distances) {
					total_cost = 0;
					max_cost = 0;
					DarpSolverHAC dshc(tasks, agentNodeIds, g);
					dshc.set_hac_properties(c, d, p);
					dshc.solve();
					r1 = dshc.getRoutes();
					for (auto& r : r1) {
						total_cost += r.cost;
						max_cost = max(max_cost, r.cost);
					}
					out_stream << total_cost << "," << max_cost << "," << dshc.assignment_time << "," << dshc.solution_time << ",";
				}
			}
			total_cost = 0;
			max_cost = 0;
			for (const string& ci : Kmeans::center_initializers) {
				for (const string& ca : Kmeans::center_assignments) {
					for (const string& ecd : Kmeans::entity_center_distances) {
						DarpSolverKmeans dskm(tasks, agentNodeIds, g, ecd, ca, ci, p);
						dskm.solve();
						for (auto& r : r1) {
							total_cost += r.cost;
							max_cost = max(max_cost, r.cost);
						}
						out_stream << total_cost << "," << max_cost << "," << dskm.assignment_time << "," << dskm.solution_time;
					}
				}
			}
		}
		out_stream << endl;
	}
	int bp = 0;
}