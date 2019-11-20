#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>

using namespace std;
class mypair
{
public:
    int first;
    int second;
    mypair(int a = 0, int b = 0):first{a},second{b} {}
    bool operator==(const mypair b)
    {
        if(first == b.first && second == b.second)
            return true;
        return false;
    }
    void operator=(mypair a)
    {
        first = a.first;
        second = a.second;
    }

};
mypair make_mypair(int a, int b)
{
    return mypair(a, b);
}



template <class T>
class MyVector
{

public:

    MyVector(): size_(0) {}

    MyVector(const MyVector &rhs) = delete;

    explicit MyVector(int n){
        data_ = new T[n];
        size_ = n;
    }

    ~MyVector()
    {
        delete [] data_;
    }

    int Size() const
    {
        return size_;
    }

    void Resize(int n);

    T &At(int i)
    {
        return data_[i];
    }

    T At(int i) const
    {
        return data_[i];
    }

    bool Empty()
    {
        if(size_ == 0)
            return true;
        return false;
    }

    T Back()
    {

        return data_[size_ - 1];
    }

    void Insert(int pos, int elem)
    {

        MyVector TempMyVector(this->size_);

        for (int i = 0; i < this->size_; ++i)
            TempMyVector.data_[i] = this->data_[i];

        delete [] this->data_;

        size_++;

        data_ = new T[size_];

        for (int i = 0; i < pos; ++i)
            data_[i] = TempMyVector.data_[i];

        this->At(pos) = elem;

        for (int i = pos+1; i < size_; ++i)
            data_[i] = TempMyVector.data_[i-1];

    }

    void Erase(int pos)
    {

        MyVector TempMyVector(this->size_);

        for (int i = 0; i < this->size_; ++i)
            TempMyVector.data_[i] = this->data_[i];

        delete [] this->data_;

        size_--;

        data_ = new T[size_];

        for (int i = 0; i < pos; ++i)
            data_[i] = TempMyVector.data_[i];

        for (int i = pos; i < size_; ++i)
            data_[i] = TempMyVector.data_[i+1];

    }

    void PushFront(T elem)
    {

        MyVector TempMyVector(this->size_);

        for (int i = 0; i < this->size_; ++i)
            TempMyVector.data_[i] = this->data_[i];

        delete [] this->data_;

        size_++;

        data_ = new T[size_];

        for (int i = 0; i < size_-1; ++i)
            data_[i+1] = TempMyVector.data_[i];

        this->At(0) = elem;

    }

    void PopFront()
    {

        MyVector TempMyVector(this->size_);

        for (int i = 0; i < this->size_; ++i)
            TempMyVector.data_[i] = this->data_[i];

        delete [] this->data_;

        size_--;

        data_ = new T[size_];

        for (int i = 0; i < size_; ++i)
            data_[i] = TempMyVector.data_[i+1];

    }

    void Clear()
    {

        for (int i = 0; i < this->size_; ++i)
            data_[i] = 0;

    }

    void PushBack(T elem)
    {

        MyVector TempMyVector(this->size_);

        for (int i = 0; i < this->size_; ++i)
            TempMyVector.data_[i] = this->data_[i];

        delete [] this->data_;

        size_++;

        data_ = new T[size_];

        for (int i = 0; i < size_-1; ++i)
            data_[i] = TempMyVector.data_[i];

        this->At(size_-1) = elem;

    }

    void PopBack()
    {

        MyVector TempMyVector(this->size_);

        for (int i = 0; i < this->size_; ++i)
            TempMyVector.data_[i] = this->data_[i];

        delete [] this->data_;

        size_--;

        data_ = new T[size_];

        for (int i = 0; i < size_; ++i)
            data_[i] = TempMyVector.data_[i];

    }

    T &operator[](int i)
    {
        return At(i);
    }

    T operator[](int i) const
    {
        return At(i);
    }
private:
    int size_;
    T *data_;

};

int house[1100][1100] = {0};
int isclean[1100][1100] = {0};
int disDFS[1100][1100] = {0};
int disBFS[1100][1100] = {0};
bool isvisit[1100][1100] = {0};
int row, col, battery, maxstep;
mypair startpos, curr;
MyVector<mypair> path;
MyVector<mypair> trueans;

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
        mypair pos;
        int step;
        pos_dis(mypair p, int s):pos{p}, step{s} {}
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
            q.push(pos_dis(make_mypair(r + 1, c), step + 1));
            disBFS[r + 1][c] = step + 1;
            visited[r + 1][c] = true;
        }
        if(r - 1 >= 1 && !visited[r - 1][c] && house[r - 1][c] == 0)
        {
            q.push(pos_dis(make_mypair(r - 1, c), step + 1));
            disBFS[r - 1][c] = step + 1;
            visited[r - 1][c] = true;
        }
        if(c + 1 <= col && !visited[r][c + 1] && house[r][c + 1] == 0)
        {
            q.push(pos_dis(make_mypair(r, c + 1), step + 1));
            disBFS[r][c + 1] = step + 1;
            visited[r][c + 1] = true;
        }
        if(c - 1 >= 1 && !visited[r][c - 1] && house[r][c - 1] == 0)
        {
            q.push(pos_dis(make_mypair(r, c - 1), step + 1));
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
void findpath(mypair point, mypair des, int total)
{
    path.PushBack(point);
    /*for(int i = 0; i < path.Size(); i++)
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
    if(path.Size() > total + 2)
    {
        //cout << "!!!!";
        path.PopBack();
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
            findpath(make_mypair(r + 1, c), des, total);
            if(isfind)
                return;
        }
        if(r - 1 >= 1 && disBFS[r - 1][c] > disBFS[r][c] && house[r - 1][c] != 1)
        {
            findpath(make_mypair(r - 1, c), des, total);
            if(isfind)
                return;
        }
        if(c + 1 <= col && disBFS[r][c + 1] > disBFS[r][c] && house[r][c + 1] != 1)
        {

            findpath(make_mypair(r, c + 1), des, total);
            if(isfind)
                return;
        }
        if(c - 1 >= 1 && disBFS[r][c - 1] > disBFS[r][c] && house[r][c - 1] != 1)
        {
            //cout << "!!!";
            findpath(make_mypair(r, c - 1), des, total);
            if(isfind)
                return;
        }
    }
    else
    {
        if(r + 1 <= row && disBFS[r + 1][c] < disBFS[r][c] && house[r + 1][c] != 1)
        {
            //cout << "!!!";
            findpath(make_mypair(r + 1, c), des, total);
            if(isfind)
                return;
        }
        if(r - 1 >= 1 && disBFS[r - 1][c] < disBFS[r][c] && house[r - 1][c] != 1)
        {
            findpath(make_mypair(r - 1, c), des, total);
            if(isfind)
                return;
        }

        if(c + 1 <= col && disBFS[r][c + 1] < disBFS[r][c] && house[r][c + 1] != 1)
        {
            findpath(make_mypair(r, c + 1), des, total);
            if(isfind)
                return;
        }
        if(c - 1 >= 1 && disBFS[r][c - 1] < disBFS[r][c] && house[r][c - 1] != 1)
        {
            findpath(make_mypair(r, c - 1), des, total);
            if(isfind)
                return;
        }
    }
    //cout << "!!!";
    path.PopBack();
}
void showpath()
{
    for(int i = 1; i < path.Size(); i++)
    {
        trueans.PushBack(path[i]);
        //cout << path[i].first << " " << path[i].second << endl;
    }

}
void clearpath()
{
    while(!path.Empty())
    {
        isclean[path.Back().first][path.Back().second] = 1;
        path.PopBack();
    }
}
void onlyclear()
{
    while(!path.Empty())
    {
        //isclean[path.back().first][path.back().second] = 1;
        path.PopBack();
    }
}
void showans()
{
    cout << trueans.Size() << endl;
    for(int i = 0; i < trueans.Size(); i++)
    {
        cout << trueans[i].first << " " << trueans[i].second << "   " << i % battery << endl;
    }
}
bool back_to_charge(mypair curr, int leaststep)
{
    findpath(curr, startpos, abs(disBFS[curr.first][curr.second] - disBFS[startpos.first][startpos.second]));
    cout << path.Size() << "   ! " << leaststep << endl;
    if(path.Size() + 1 < leaststep)
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
    trueans.PushBack(startpos);
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
                findpath(curr, make_mypair(r + 1, c), abs(disBFS[curr.first][curr.second] - disBFS[r + 1][c]));
            }
            else if(r - 1 >= 1 && disBFS[r - 1][c] > disBFS[r][c] && house[r - 1][c] != 1 && isclean[r - 1][c] == 0)
            {
                findpath(curr, make_mypair(r - 1, c), abs(disBFS[curr.first][curr.second] - disBFS[r - 1][c]));
            }
            else if(c + 1 <= col && disBFS[r][c + 1] > disBFS[r][c] && house[r][c + 1] != 1 && isclean[r][c + 1] == 0)
            {
                findpath(curr, make_mypair(r, c + 1), abs(disBFS[curr.first][curr.second] - disBFS[r][c + 1]));
            }
            else if(c - 1 >= 1 && disBFS[r][c - 1] > disBFS[r][c] && house[r][c - 1] != 1 && isclean[r][c - 1] == 0)
            {
                findpath(curr, make_mypair(r, c - 1), abs(disBFS[curr.first][curr.second] - disBFS[r][c - 1]));
            }
            else
            {
                //cout << "!!!";
                int minstep = maxstep;
                mypair tar;
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
                //cout << "!!!!" << path.Size() << "!!!";
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
                if(path.Size() == 0)
                {
                    break;
                }
                int gostep = path.Size() - 1;
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

            curr = make_mypair(path.Back().first, path.Back().second);
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
    /*findpath(make_mypair(3, 3), make_mypair(3, 8), abs(disBFS[3][3] - disBFS[3][8]));
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
