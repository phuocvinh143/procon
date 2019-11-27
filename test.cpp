#include<bits/stdc++.h>

#define F first
#define S second

using namespace std;

struct Point{
    int x, y;
};

vector<Point> Agents, Enemy_agents, vt_delete_cmd;
pair<int, int> MAP[25][25];

// 0: no title, no agent
// 1: agent 2 title
// 2: agent 2
// 3: agent 1 title
// 4: agent 1

int n_row, m_col, agent_number;

void random_map() {
    n_row = rand()%11 + 10;
    m_col = rand()%11 + 10;


    for (int i = 1; i <= (n_row % 2 ? n_row/2 + 1 : n_row/2); ++i) {
        for (int j = 1; j <= (m_col % 2 ? m_col/2 + 1 : m_col/2); ++j) {
            int ad = rand()%2;
            int value = rand()%17;
            value = (ad ? -value : value);
            MAP[i][j].F = value;
            MAP[n_row-i+1][j].F = value;
            MAP[i][m_col-j+1].F = value;
            MAP[n_row-i+1][m_col-j+1].F = value;
        }
    }
}

void random_agent_coordinate() {
    Point a;
    a.x = 2; a.y = 2;
    Agents.push_back(a);

    a.x = 6; a.y = 3;
    Agents.push_back(a);

    a.x = 3; a.y = 9;
    Agents.push_back(a);

    a.x = 7; a.y = 10;
    Agents.push_back(a);

    a.x = 2; a.y = 10;
    Enemy_agents.push_back(a);

    a.x = 3; a.y = 3;
    Enemy_agents.push_back(a);

    a.x = 7; a.y = 2;
    Enemy_agents.push_back(a);

    a.x = 6; a.y = 9;
    Enemy_agents.push_back(a);

    for (int i = 0; i < Agents.size(); ++i) {
        MAP[Agents[i].x][Agents[i].y].F = 0;
        MAP[Agents[i].x][Agents[i].y].S = 4;

        MAP[Enemy_agents[i].x][Enemy_agents[i].y].F = 0;
        MAP[Enemy_agents[i].x][Enemy_agents[i].y].S = 2;
    }
}

//team1: score
//team2: destroy enemy team

// clockwise
int dx[] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dy[] = {0, 1, 1, 1, 0, -1, -1, -1};

int inside(int x, int y) {
    if (x >= 1 && x <= n_row && y >= 1 && y <= m_col) return 1;
    return 0;
}

Point team1_move(Point P) {
    Point tmp;
    vector<pair<int, pair<int, pair<int, int> > > > vt_coor;
    vt_coor.clear();
    for (int i = 0; i < 8; ++i) {
        int x = dx[i] + P.x;
        int y = dy[i] + P.y;
        if (inside(x, y)) {
            vt_coor.push_back(make_pair(MAP[x][y].S, make_pair(-MAP[x][y].F, make_pair(x, y))));
        }
    }
    sort(vt_coor.begin(), vt_coor.end()); //sort by priority of status
    if (vt_coor[0].F == 0 || vt_coor[0].F == 3) { // empty cell or team's title
        tmp.x = vt_coor[0].S.S.F;
        tmp.y = vt_coor[0].S.S.S;
        return tmp;
    }
    if (vt_coor[0].F == 1 || vt_coor[0].F == 2) { // enemy title
        tmp.x = vt_coor[0].S.S.F;
        tmp.y = vt_coor[0].S.S.S;
        vt_delete_cmd.push_back(tmp);
        tmp.x = P.x;
        tmp.y = P.y;
        return tmp;
    }
    if (vt_coor[0].F == 4) {
        tmp.x = P.x;
        tmp.y = P.y;
        return tmp;
    }
}

Point team2_move(Point P) {
    Point tmp;
    return tmp;
}

void update_agent_coordinate() {
    for (int i = 0; i < Agents.size(); ++i) {
        Point tmp = Agents[i];
        Agents[i] = team1_move(tmp);
//        tmp = Agents[i+Agents.size()/2];
//        Agents[i+Agents.size()/2] = team2_move(tmp);
    }
    // return new coordinate and delete title command
    for (int i = 0; i < Agents.size(); ++i) {
        MAP[Agents[i].x][Agents[i].y].S = 3;
    }
    vt_delete_cmd.clear();
//    for (int i = 0; i < Agents.size()/2; ++i) {
//        Point tmp = Agents[i];
//        Agents[i] = team1_move(tmp);
//        tmp = Agents[i+Agents.size()/2];
//        Agents[i+Agents.size()/2] = team2_move(tmp);
//    }

}

void print_map() {
    for (int i = 1; i <= n_row; ++i) {
        for (int j = 1; j <= m_col; ++j) {
            if (!MAP[i][j].S) cout << MAP[i][j].F << "\t";
            else if (MAP[i][j].S == 1 || MAP[i][j].S == 2) cout << "*\t";
            else cout << "x\t";
        }
        cout << endl;
    }
}

void print_score() {
    int enemy_score = 0, my_score = 0;
    for (int i = 1; i <= n_row; ++i) {
        for (int j = 1; j <= m_col; ++j) {
            if (!MAP[i][j].S) continue;
            else if (MAP[i][j].S == 1 || MAP[i][j].S == 2) enemy_score += MAP[i][j].F;
            else my_score += MAP[i][j].F;
        }
    }
    cout << "My team score: " << my_score << endl << "Enemy team's score: " << enemy_score << endl;
}

int main(){
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);

    srand(time(NULL));

    random_map();
    random_agent_coordinate();

//    read_coordinate_of_agent(json_file);

//    print_map();
    int turns; cin >> turns;
    while (turns--) {
        update_agent_coordinate();
        print_map();
        system("pause");
        system("cls");
    }
    print_score();
    return 0;
}
