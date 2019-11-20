#include <iostream>
#include <vector>
#include <utility>
#include <queue>

using namespace std;

int house[1100][1100] = {0};
int isclean[1100][1100] = {0};
int disDFS[1100][1100] = {0};
int disBFS[1100][1100] = {0};
bool isvisit[1100][1100] = {0};
int row, col, battery, maxstep;
pair<int, int> startpos, curr;
vector<pair<int, int>> path;
vector<pair<int, int>> trueans;

void makedisDFS(int step, int r, int c)
{
    disDFS[r][c] = step;
    isvisit[r][c] = true;
    if(r + 1 <= row && !isvisit[r + 1][c] && house[r + 1][c] == 0)
        makedisDFS(step + 1, r + 1, c);

    if(r - 1 >= 1 && !isvisit[r - 1][c] && house[r - 1][c] == 0)
        makedisDFS(step + 1, r - 1, c);

    if(c + 1 <= col && !isvisit[r][c + 1] && house[r][c + 1] == 0)
        makedisDFS(step + 1, r, c + 1);

    if(c - 1 >= 1 && !isvisit[r][c - 1] && house[r][c - 1] == 0)
        makedisDFS(step + 1, r, c - 1);
}

void makedisBFS()
{
    bool visited[1100][1100] = {0};
    class pos_dis
    {
    public:
        pair<int, int> pos;
        int step;
        pos_dis(pair<int, int> p, int s):pos{p}, step{s} {}
    };
    queue<pos_dis> q;

    q.push(pos_dis(startpos, 0));
    visited[startpos.first][startpos.second] = true;
    while(!q.empty())
    {
        int r = q.front().pos.first;
        int c = q.front().pos.second;
        int step = q.front().step;
        q.pop();
        if(r + 1 <= row && !visited[r + 1][c] && house[r + 1][c] == 0)
        {
            q.push(pos_dis(make_pair(r + 1, c), step + 1));
            disBFS[r + 1][c] = step + 1;
            visited[r + 1][c] = true;
        }
        if(r - 1 >= 1 && !visited[r - 1][c] && house[r - 1][c] == 0)
        {
            q.push(pos_dis(make_pair(r - 1, c), step + 1));
            disBFS[r - 1][c] = step + 1;
            visited[r - 1][c] = true;
        }
        if(c + 1 <= col && !visited[r][c + 1] && house[r][c + 1] == 0)
        {
            q.push(pos_dis(make_pair(r, c + 1), step + 1));
            disBFS[r][c + 1] = step + 1;
            visited[r][c + 1] = true;
        }
        if(c - 1 >= 1 && !visited[r][c - 1] && house[r][c - 1] == 0)
        {
            q.push(pos_dis(make_pair(r, c - 1), step + 1));
            disBFS[r][c - 1] = step + 1;
            visited[r][c - 1] = true;
        }
    }
}
bool check_clean()
{
    for(int i = 1; i <= row; i++)
    {
        for(int j = 1; j <= col; j++)
        {
            if(house[i][j] == 0 && isclean[i][j] == 0)
                return false;
        }
    }
    return true;
}
bool isfind = false;
void findpath(pair<int, int> point, pair<int, int> des, int total)
{
    path.push_back(point);
    /*for(int i = 0; i < path.size(); i++)
    {
        cout << path[i].first << " " << path[i].second << endl;
    }
    cout << endl;//*/

    if(point == des)
    {
        //cout << "!!!!";
        isfind = true;
        return;
    }
    if(path.size() > total + 2)
    {
        //cout << "!!!!";
        path.pop_back();
        return;
    }
    bool way = false;
    if(disBFS[point.first][point.second] - disBFS[des.first][des.second] < 0)
    {
        way = true;
    }
    int r = point.first;
    int c = point.second;
    if(way)
    {
        //cout << "!!!";
        if(r + 1 <= row && disBFS[r + 1][c] > disBFS[r][c] && house[r + 1][c] != 1)
        {
            findpath(make_pair(r + 1, c), des, total);
            if(isfind)
                return;
        }
        if(r - 1 >= 1 && disBFS[r - 1][c] > disBFS[r][c] && house[r - 1][c] != 1)
        {
            findpath(make_pair(r - 1, c), des, total);
            if(isfind)
                return;
        }
        if(c + 1 <= col && disBFS[r][c + 1] > disBFS[r][c] && house[r][c + 1] != 1)
        {

            findpath(make_pair(r, c + 1), des, total);
            if(isfind)
                return;
        }
        if(c - 1 >= 1 && disBFS[r][c - 1] > disBFS[r][c] && house[r][c - 1] != 1)
        {
            //cout << "!!!";
            findpath(make_pair(r, c - 1), des, total);
            if(isfind)
                return;
        }
    }
    else
    {
        if(r + 1 <= row && disBFS[r + 1][c] < disBFS[r][c] && house[r + 1][c] != 1)
        {
            //cout << "!!!";
            findpath(make_pair(r + 1, c), des, total);
            if(isfind)
                return;
        }
        if(r - 1 >= 1 && disBFS[r - 1][c] < disBFS[r][c] && house[r - 1][c] != 1)
        {
            findpath(make_pair(r - 1, c), des, total);
            if(isfind)
                return;
        }

        if(c + 1 <= col && disBFS[r][c + 1] < disBFS[r][c] && house[r][c + 1] != 1)
        {
            findpath(make_pair(r, c + 1), des, total);
            if(isfind)
                return;
        }
        if(c - 1 >= 1 && disBFS[r][c - 1] < disBFS[r][c] && house[r][c - 1] != 1)
        {
            findpath(make_pair(r, c - 1), des, total);
            if(isfind)
                return;
        }
    }
    //cout << "!!!";
    path.pop_back();
}
void showpath()
{
    for(int i = 1; i < path.size(); i++)
    {
        trueans.push_back(path[i]);
        //cout << path[i].first << " " << path[i].second << endl;
    }

}
void clearpath()
{
    while(!path.empty())
    {
        isclean[path.back().first][path.back().second] = 1;
        path.pop_back();
    }
}
void onlyclear()
{
    while(!path.empty())
    {
        //isclean[path.back().first][path.back().second] = 1;
        path.pop_back();
    }
}
void showans()
{
    cout << trueans.size() << endl;
    for(int i = 0; i < trueans.size(); i++)
    {
        cout << trueans[i].first << " " << trueans[i].second << "   " << i % battery << endl;
    }
}
bool back_to_charge(pair<int, int> curr, int leaststep)
{
    findpath(curr, startpos, abs(disBFS[curr.first][curr.second] - disBFS[startpos.first][startpos.second]));
    cout << path.size() << "   ! " << leaststep << endl;
    if(path.size() + 1 < leaststep)
    {
        clearpath();
        return true;
    }
    else
    {
        clearpath();
        return false;
    }

}
int main()
{
    cin >> row >> col >> battery;
    maxstep = battery;
    for(int i = 1; i <= row; i++)
    {
        for(int j = 1; j <= col; j++)
        {
            char a;
            cin >> a;
            if(a == 'R')// -1 means R
            {
                startpos.first = i;
                startpos.second = j;
                house[i][j] = -1;
            }
            else
            {
                house[i][j] = a - '0';
            }
        }
    }

    /*for(int i = 1; i <= row; i++)
    {
        for(int j = 1; j <= col; j++)
        {
            cout << house[i][j] ;
        }
        cout << endl;
    }*/
    //makedisDFS(0, start_row, start_col);
    makedisBFS();
    curr = startpos;
    trueans.push_back(startpos);
    while(!check_clean())
    {
        int leaststep = maxstep;
        curr = startpos;
        //cout << "!!!";
        while(back_to_charge(curr, leaststep))
        {

            //cout << "!!";
            int r = curr.first;
            int c = curr.second;
            isfind = false;
            if(r + 1 <= row && disBFS[r + 1][c] > disBFS[r][c] && house[r + 1][c] != 1 && isclean[r + 1][c] == 0)
            {
                findpath(curr, make_pair(r + 1, c), abs(disBFS[curr.first][curr.second] - disBFS[r + 1][c]));
            }
            else if(r - 1 >= 1 && disBFS[r - 1][c] > disBFS[r][c] && house[r - 1][c] != 1 && isclean[r - 1][c] == 0)
            {
                findpath(curr, make_pair(r - 1, c), abs(disBFS[curr.first][curr.second] - disBFS[r - 1][c]));
            }
            else if(c + 1 <= col && disBFS[r][c + 1] > disBFS[r][c] && house[r][c + 1] != 1 && isclean[r][c + 1] == 0)
            {
                findpath(curr, make_pair(r, c + 1), abs(disBFS[curr.first][curr.second] - disBFS[r][c + 1]));
            }
            else if(c - 1 >= 1 && disBFS[r][c - 1] > disBFS[r][c] && house[r][c - 1] != 1 && isclean[r][c - 1] == 0)
            {
                findpath(curr, make_pair(r, c - 1), abs(disBFS[curr.first][curr.second] - disBFS[r][c - 1]));
            }
            else
            {
                //cout << "!!!";
                int minstep = maxstep;
                pair<int, int> tar;
                for(int i = 1; i <= row; i++)
                {
                    for(int j = 1; j <= col; j++)
                    {
                        if(house[i][j] == 0 && isclean[i][j] == 0)
                        {
                            if(disBFS[i][j] < minstep)
                                minstep = disBFS[i][j];
                            tar.first = i;
                            tar.second = j;
                        }
                    }
                }
                //cout << "!!!!" << minstep << "!!!";
                findpath(curr, tar, abs(disBFS[curr.first][curr.second] - disBFS[tar.first][tar.second]));
                //cout << "!!!!" << path.size() << "!!!";
                //cout << endl;

                /*for(int i = 1; i <= row; i++)
                {
                    for(int j = 1; j <= col; j++)
                    {
                        cout << isclean[i][j];
                    }
                    cout << endl;
                }
                cout << endl;//*/
                if(path.size() == 0)
                {
                    break;
                }
                int gostep = path.size() - 1;
                //onlyclear();
                //findpath(tar, startpos, abs(disBFS[startpos.first][startpos.second] - disBFS[tar.first][tar.second]));
                int backstep = abs(disBFS[startpos.first][startpos.second] - disBFS[tar.first][tar.second]);

                if(gostep + backstep > leaststep)
                {
                    onlyclear();
                    break;
                }
                else
                {
                    //onlyclear();
                    leaststep = leaststep - gostep + 1;
                    //findpath(curr, tar, abs(disBFS[curr.first][curr.second] - disBFS[tar.first][tar.second]));
                }

            }

            curr = make_pair(path.back().first, path.back().second);
            showpath();
            clearpath();
            leaststep--;
            //cout << "!!!" << leaststep << "!!!";
        }
        findpath(curr, startpos, abs(disBFS[curr.first][curr.second] - disBFS[startpos.first][startpos.second]));
        showpath();
        clearpath();
        /*cout << endl;
        for(int i = 1; i <= row; i++)
        {
            for(int j = 1; j <= col; j++)
            {
                cout << isclean[i][j];
            }
            cout << endl;
        }
        cout << endl;//*/
    }//*/
    /*findpath(make_pair(3, 3), make_pair(3, 8), abs(disBFS[3][3] - disBFS[3][8]));
    showpath();
    clearpath();//*/
    cout << endl;
    for(int i = 1; i <= row; i++)
    {
        for(int j = 1; j <= col; j++)
        {
            cout << isclean[i][j];
        }
        cout << endl;
    }
    cout << endl;
    showans();
    return 0;

}
