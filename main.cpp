#include<bits/stdc++.h>

using namespace std;

struct user {
	int id;
	string username;
	string password;
	string name;
	string Gmail;
};

struct question {
	int id;
	int id_to;
	int id_from;
	string ques;
	string ans;
	question (int id=-1,int id_to = -1,int id_from = -1,string ques="", string ans="") :
		id(id), id_to(id_to), id_from(id_from), ques(ques),ans(ans)
	{}
};

void check_file(ifstream& x,string s="") {
	if (x.fail()) 
		cout << "\nCan't Open "<<s<<" file";
}
void check_file(ofstream& x,string s="") {
	if (x.fail())
		cout << "\nCan't Open "<<s<<" file";
}

void download_data(vector<user>& users,vector<question>&questions) {
	ifstream fin("users.txt");
	check_file(fin, "users.txt");
	while (!fin.fail()) {
		user tmp;
		// id useer pass name mail from to 
		fin >> tmp.id;
		fin >> tmp.username;
		fin >> tmp.password;
		fin >> tmp.name;
		fin >> tmp.Gmail;
		if (tmp.Gmail.empty())continue;
		users.push_back(tmp);
	}
	fin.close();
	fin.open("questions.txt");
	check_file(fin, "questions.txt");
	while (!fin.fail()) {
		question tmp;
		// id to from q a 
		fin >> tmp.id;
		fin >> tmp.id_from;
		fin >> tmp.id_to;
		fin.ignore();
		getline(fin, tmp.ques);
		getline(fin, tmp.ans);
		if (tmp.ques.empty())continue;
		questions.push_back(tmp);
	}
}
void upload_data(vector<user>& users, vector<question>& questions) {

	ofstream fout("users.txt");
	check_file(fout, "users.txt");
	for (auto it : users) {
		fout << it.id << ' ';
		fout << it.username << ' ';
		fout << it.password << ' ';
		fout << it.name << ' ';
		fout << it.Gmail << '\n';
	}
	fout.close();
	fout.open("questions.txt");
	check_file(fout, "questions.txt");
	for (auto it : questions) {
		fout << it.id << ' ';
		fout << it.id_from << ' ';
		fout << it.id_to << '\n';
		fout << it.ques << '\n';
		fout << it.ans << '\n';
	}
}


class manage {

	int check_acount(vector<user>& users,string user_,string pass_) {
		int i = 0;
		for (auto it : users) {
			i++;
			if (it.username == user_) {
				return ((pass_ == it.password) * i);
			}
		}
		return -1;
	}

	string get_user(vector<user>& users) {
		string s;
		int ret = 0;
		while (ret==0) {
			cin >> s;
			ret = 1;
			for (auto it : users) {
				if (it.username == s) {
					cout << "\nEnter another username : ";
					ret = 0;
					break;
				}
			}
		}
		return s;
	}

	string get_mail(vector<user>& users) {
		string s; cin >> s;
		while (1) {
			if (!valid_mail(s)||!uniqe_mail(users,s)) {
				cout << "\nEnter another mail : "; cin >> s;
				continue;
			}
			return s;
		}
	}

	bool valid_mail(string Gmail) {
		bool dot = 0, att = 0;
		for (int i = 0; i < Gmail.size(); i++) {
			char it = Gmail[i];
			if (it == '.') {
				if (dot || !att || i == 0 || Gmail[i - 1] == '@' || i == Gmail.size() - 1)return 0;
				dot = 1;
			}
			if (it == '@') {
				if (att || i == 0)return 0;
				att = 1;
			}
		}
		return dot and att;
	}

	bool uniqe_mail(vector<user>& users,string s) {
		for (auto it : users) {
			if (it.Gmail == s)return 0;
		}
		return 1;
	}

	void show_my_data(int id, vector<user>& users) {
		id--;
		cout << users[id].id << '\n';
		cout << users[id].username << '\n';
		cout << users[id].password << '\n';
		cout << users[id].name << '\n';
		cout << users[id].Gmail << '\n';
	}

	int choose_forward(vector<user>& users) {
		int id=-1;
		while (id < 0) {
			show_server_data(users);
			cout << "\nEnter id : "; cin >> id;
			if (id > users.size() || id < 1) {
				cout << "\nInvalid ID";
				id = -1;
			}
		}
		system("CLS");
		return id;
	}

	void show_server_ques(vector<question>& questions) {
		for (auto it : questions) {
			cout << '\n' << it.id << ' ' <<it.id_from <<
				' ' << it.id_to << ' ' << it.ques << '\n' << it.ans << "\n\n";
		}
	}

public:
	int log_in(vector<user>&users) {
		string user_;
		string pass_;
		int ret_id = 0;
		while (ret_id<1) {
			cout << "\nEnter your username : "; cin >> user_;
			cout << "\nEnter your password : "; cin >> pass_;
			system("CLS");
			ret_id = check_acount(users,user_,pass_);
			if (ret_id == 0) {
				cout << "\nIncorrect password";
			}
			else if (ret_id == -1) {
				cout << "\nYour acound not founded";
				cout << "\nif you want reprocess enter 1";
				cout << "\nif you want sign up enter 2";
				int op;
				cout << "\nEnter : "; cin >> op;
				system("CLS");
				if (op == 2)return -1;
				else continue;
			}
		}
		return ret_id;
	}

	int sign_up(vector<user>& users) {
		user tmp;
		cout << "\nEnter your User : "; tmp.username=get_user(users);
		cout << "\nEnter your password : "; cin>>tmp.password;
		cout << "\nEnter your name : "; cin >> tmp.name;
		cout << "\nEnter your Gmail : "; tmp.Gmail=get_mail(users);
		tmp.id = users.size() + 1;
		users.push_back(tmp);
		system("CLS");
		return users.back().id;
	}

	void show_server_data(vector<user>& users) {
		for (auto it : users) {
			cout << '\n' << it.id << ' ' << it.username;
		}
		cout << '\n';
	}

	void show_questions_to_me(int id, vector<user>& users, vector<question>& questions) {
		bool have_q=0;
		for (auto& it : questions) {
			if (it.id_to == id) {
				have_q = 1;
				//From . username . (.name.) [.id.]\n
				cout << "\nFrom " << users[it.id_from - 1].username <<
					" ( " << users[it.id_from - 1].name << " ) [ " << it.id << " ] : \n";
				cout << "Question : " << it.ques << '\n';
				if (it.ans.empty())cout << "No answers yet\n";
				else
					cout << "Answer : " << it.ans << '\n';
			}
		}
		if (!have_q)cout << "\nyou haven't questions";
		cout << "\n";
	}

	void show_questions_from_me(int id, vector<user>& users,vector<question>questions) {
		bool have_q = 0;
		for (auto it : questions) {
			if (it.id_from == id) {
				cout << "\To " << users[it.id_to - 1].username <<
					" ( " << users[it.id_to-1].name << " ) [ " << users[it.id_to-1].id << " ] : \n";
				cout << "Question : " << it.ques << '\n';
				if (it.ans.empty())cout << "No answers yet\n";
				else
					cout << "Answer : " << it.ans << '\n';
				have_q = 1;
			}
		}
		if (!have_q)cout << "\nyou haven't questions";
		cout << "\n";
	}

	void add_new_ques(int my_id,vector<user>& users, vector<question>& questions) {
		int foreward = choose_forward(users);

		question tmp;
		tmp.id_from = my_id;
		tmp.id_to = foreward;
		tmp.id = questions.size() + 1;
		cout << "\nEnter your question : ";
		cin.ignore();
		getline(cin, tmp.ques);
		questions.push_back(tmp);
		system("CLS");
	}

	void respond_ques(int my_id, vector<user>& users, vector<question>& questions) {
		int id=-1;
		while (id < 0) {
			show_questions_to_me(my_id, users, questions);
			cout << "\nChoose id question : "; cin >> id;
			if (id > questions.size()) {
				id = -1;
				cout << "\nWrong question !!";
				continue;
			}
			for (auto& it : questions) {
				if (it.id == id) {
					if (it.id_to != my_id) {
						id = -1;
						cout << "\nWrong question !!";
						break;
					}
					cin.ignore();
					cout << "\nEnrter your answer : ";
					getline(cin, it.ans);
					system("CLS");
					return;
				}
			}
		}
	}

};


int main() {
	vector<user>users;
	vector<question>questions;
	download_data(users, questions);
	manage manager_system;
	//int cur_id = 1;
	int cur_id = 0;
	while (1) {
		while (cur_id < 1) {
			cout << "\n1 : Log  in";
			cout << "\n2 : Sign up";
			cout << "\n3 : Stop prog";
			int op;
			cout << "\nEnter : "; cin >> op;
			system("CLS");

			if (op == 1) {
				cur_id = manager_system.log_in(users);
			}
			else if (op == 2) {
				cur_id = manager_system.sign_up(users);
			}
			else if (op == 3) {
				break;
			}
			else cout << "\nError!!\n";
		}
		if (cur_id < 1)break;
		cout << " \nEnter 1 to show questions forwarded to you";
		cout << " \nEnter 2 to show your questions";
		cout << " \nEnter 3 to ask a new questions";
		cout << " \nEnter 4 to respond a questions";
		cout << " \nEnter 5 to show all users in system";
		cout << " \nEnter 6 to delete a question";
		cout << " \nEnter 7 to log out";
		cout << " \nEnter 0 to EXIT!";
		int op; cout << "\n\nEnter : "; cin >> op;
		system("CLS");

		if (op == 1) {
			manager_system.show_questions_to_me(cur_id, users, questions);
		}
		else if (op == 2) {
			manager_system.show_questions_from_me(cur_id, users, questions);
		}
		else if (op == 3) {
			manager_system.add_new_ques(cur_id, users, questions);
		}
		else if (op == 4) {
			manager_system.respond_ques(cur_id, users, questions);
		}
		else if (op == 5) {
			manager_system.show_server_data(users);
		}
		else if (op == 6) {

		}
		else if (op == 7)
			cur_id = -1;
		else if (op == 0)
			break;
	}
	upload_data(users, questions);
	return 0; 

}