#include <iostream>
#include <list>
#include <map>
#include <vector>
#include <queue>
#include <cmath>


using namespace std;

int getDigit(int number, int pos)
{
    int currentField = number;
    for (int i = 0; i < pos; ++i)
    {
        currentField /= 10;
    }
    return currentField % 10;
}


struct Field
{
    Field(){}
    Field(vector<int> &start)
    {
        fieldPosition = 0;
        for (int i = 0; i < 9; ++i)
        {
            setNumber(start[i], i);
            if (start[i] == 0)
            {
                Hole = i;
            }
        }
    }

    Field(const Field &field) : fieldPosition(field.fieldPosition), Hole(field.Hole) {}

    void setNumber(int value, int pos);

    int getNumber(int pos) const;

    bool hasSolution() const;

    Field Right() const;

    Field Left() const;

    Field Up() const;

    Field Down() const;

    int fieldPosition;
    int previous;
    int Hole;
    char Move;
};

bool Field::hasSolution() const
{
    int Inversions = 0;

    for (int i = 0; i < 9; ++i)
    {
        for (int j = i + 1; j < 9; ++j)
        {
            if (getNumber(i) != 0 && getNumber(j) != 0)
            {
                if (getNumber(i) > getNumber(j))
                {
                    ++Inversions;
                }
            }
        }
    }

    if (Inversions % 2 == 1)
        return false;
    else
        return true;
}

int Field::getNumber(int pos) const
{
    return getDigit(fieldPosition, pos);
}

void Field::setNumber(int value, int pos)
{
    int k = pow(10, pos);
    fieldPosition -= getDigit(fieldPosition, pos) * k;
    fieldPosition += value * k;
}

Field Field::Right() const
{
    Field ChangedField(*this);
    ChangedField.Move = 'R';
    ChangedField.previous = fieldPosition;

    int Current = getNumber(Hole + 1);
    ChangedField.setNumber(Current, Hole);
    ChangedField.setNumber(0, Hole + 1);
    ChangedField.Hole += 1;

    return ChangedField;

}

Field Field::Left() const
{
    Field ChangedField(*this);
    ChangedField.Move = 'L';
    ChangedField.previous = fieldPosition;

    int Current = getNumber(Hole - 1);
    ChangedField.setNumber(Current, Hole);
    ChangedField.setNumber(0, Hole - 1);
    ChangedField.Hole -= 1;

    return ChangedField;

}

Field Field::Up() const
{
    Field ChangedField(*this);
    ChangedField.Move = 'U';
    ChangedField.previous = fieldPosition;

    int Current = getNumber(Hole - 3);
    ChangedField.setNumber(Current, Hole);
    ChangedField.setNumber(0, Hole - 3);
    ChangedField.Hole -= 3;

    return ChangedField;

}

Field Field::Down() const
{
    Field ChangedField(*this);
    ChangedField.Move = 'D';
    ChangedField.previous = fieldPosition;

    int Current = getNumber(Hole + 3);
    ChangedField.setNumber(Current, Hole);
    ChangedField.setNumber(0, Hole + 3);
    ChangedField.Hole += 3;

    return ChangedField;

}

class CGameSolver
{
public:
    bool getPath(const Field &start, list<char> &path);

private:
    void visited(const Field &field);

    queue<int> Queue;
    map<int, Field> fields;
};

bool CGameSolver::getPath(const Field &start, list<char> &path)
{
    path.clear();

    if (!start.hasSolution())
    {
        return false;
    }

    fields[start.fieldPosition] = start;
    Queue.emplace(start.fieldPosition);

    int fieldPosition;
    while (1)
    {
        fieldPosition = Queue.front();
        Queue.pop();

        if (fieldPosition == 87654321)
        {
            break;
        }

        Field currentField = fields[fieldPosition];

        if (currentField.Hole % 3 != 0)
        {
            visited(currentField.Left());
        }
        if (currentField.Hole % 3 != 2)
        {
            visited(currentField.Right());
        }
        if (currentField.Hole >= 3)
        {
            visited(currentField.Up());
        }
        if (currentField.Hole <= 5)
        {
            visited(currentField.Down());
        }

    }

    while (fieldPosition != start.fieldPosition)
    {
        path.push_front(fields[fieldPosition].Move);
        fieldPosition = fields[fieldPosition].previous;
    }

    return true;
}

void CGameSolver::visited(const Field &field)
{
    if (fields.find(field.fieldPosition) == fields.end())
    {
        fields[field.fieldPosition] = field;
        Queue.emplace(field.fieldPosition);
    }
}

int main()
{
    vector<int> values;

    for (int i = 0; i < 9; ++i)
    {
        int a;
        cin >> a;
        values.push_back(a);
    }

    Field field(values);
    CGameSolver answer;
    list<char> path;
    if (!answer.getPath(field, path))
    {
        cout << -1;
    }

    else
    {
        cout << path.size() << endl;
        for (char c: path)
        {
            cout << c;
        }
    }

    return 0;
}