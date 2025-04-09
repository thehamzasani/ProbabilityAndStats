#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

bool hasDecimalValue(float number)
{
    double integerPart;
    double fractionalPart = modf(number, &integerPart);
    return fractionalPart != 0.0;
};

class IntervalsOfGroupedData
{
public:
    float lowerLimit;
    float upperLimit;
    int frequency;
    float gap;
    float midpoint;
    vector<float> entries;
};

class Formulas
{

public:
    vector<float> data = {
        106, 107, 76, 82, 109, 107, 115, 93, 187, 95, 123, 125,
        111, 92, 86, 70, 126, 68, 130, 129, 139, 119, 115, 128,
        100, 186, 84, 99, 113, 204, 111, 141, 136, 123, 90, 115,
        98, 110, 78, 185, 162, 178, 140, 152, 173, 146, 158, 194,
        148, 90, 107, 181, 131, 75, 184, 104, 110, 80, 118, 82};
    vector<IntervalsOfGroupedData> Intervals;
    vector<float> userData;

    int numberOfIntervals;
    Formulas(int numberOfIntervals)
    {
        this->numberOfIntervals = numberOfIntervals;
    };

    void makingIntervals(vector<float>& data)
    {
        int max = data.front();
        int min = data.front();
        for (int i = 0; i < data.size(); i++)
        {
            if (max < data[i])
            {
                max = data[i];
            }
            if (min > data[i])
            {
                min = data[i];
            }
        }

        float range = max - min;
        float intervalWidth = range / numberOfIntervals;
        int finalIntervalWidth;
        if (hasDecimalValue(intervalWidth))
        {
            finalIntervalWidth = intervalWidth + 1;
        }
        else
        {
            finalIntervalWidth = intervalWidth;
        }

        cout << "Interval Width: " << intervalWidth << endl;
        cout << "Range: " << range << endl;
        cout << "Final Interval Width: " << finalIntervalWidth << endl;
        int l = min;
        int u;
        for (int i = 0; i < numberOfIntervals; i++)
        {
            u = l + finalIntervalWidth;
            IntervalsOfGroupedData interval;
            interval.lowerLimit = l;
            interval.upperLimit = u;
            interval.gap = 1;
           
            interval.midpoint = (l+u)/2;

            interval.frequency = 0;
            for (int i = 0; i < data.size(); i++)
            {
                if (data[i] >= l && data[i] <= u)
                {
                    interval.frequency++;
                    interval.entries.push_back(data[i]);
                }
            }
            Intervals.push_back(interval);
            l = u +1;
        }
    };

    void defaultData(){
        Intervals.clear();
        makingIntervals(data);
    }

    void userInputData(){
        Intervals.clear();
        int amount;
        cout << "Enter the amount of data : ";
        cin >> amount;
        for (int i = 0; i < amount; i++)
        {
            float value;
            cout << "Enter the value of element " << i+1 << " : " << endl;
            cin >> value;
            userData.push_back(value);
        }
        
        
        makingIntervals(userData);
    };

    void display(){
        cout << "Frequency Distribution:\n";
        cout << "Interval\tFrequency\tMidpoint\tEntries\n";
        for (const auto& interval : Intervals) {
            cout << "[" << interval.lowerLimit << " - " << interval.upperLimit << "]\t\t"
                 << interval.frequency << "\t\t"
                 << interval.midpoint << "\t\t";
            for (float entry : interval.entries) {
                cout << entry << " ";
            }
            cout << endl;
        }
    }
};

int main()
{   
    int totalIntervals;
    int choice;
  
    
    // cout << "1) Grouped Data";
    // cout << "2) Ungrouped Data";

    // cout << "Enter your choice : ";
    // cin >> choice;
    
    
    

    while (true)
    {

        cout << "0) To exit Program" << endl;
        cout << "1) Default Data" <<  endl;
        cout << "2) Input Data" << endl;
        cout << "Enter your choice : ";
        cin >> choice;
        
        if (choice == 1)
        {
            Formulas f(totalIntervals);
            f.defaultData();
            f.display();
        
        }
        else if (choice == 2)
        {
            cout << "How many intervals of data do you want to make? : ";
            cin >> totalIntervals;
            Formulas f(totalIntervals);
            f.userInputData();
            f.display();
        }
        else if(choice == 0){
            cout << "Khuda Hafiz Program changa lagya te review ker deyo hamza nu" << endl;
            return false;
        }
        else
        {
            cout << "vekh ke input ker choice vicho!!!";
            continue;
        }
        
    }
    
  
    
    

    
   



    return 0;
}

// gap = upperLimit (of first class) - lowerLimit (of second class)

// int max = userData.front();
        // int min = userData.front();
        // for (int i = 0; i < userData.size(); i++)
        // {
        //     if (max < userData[i])
        //     {
        //         max = userData[i];
        //     }
        //     if (min > userData[i])
        //     {
        //         min = userData[i];
        //     }
        // }

        // float range = max - min;
        // float intervalWidth = range / numberOfIntervals;
        // int finalIntervalWidth;
        // if (hasDecimalValue(intervalWidth))
        // {
        //     finalIntervalWidth = intervalWidth + 1;
        // }
        // else
        // {
        //     finalIntervalWidth = intervalWidth;
        // }

        // cout << "Interval Width: " << intervalWidth << endl;
        // cout << "Range: " << range << endl;
        // cout << "Final Interval Width: " << finalIntervalWidth << endl;
        // int l = min;
        // int u;
        // for (int i = 0; i < numberOfIntervals; i++)
        // {
        //     u = l + finalIntervalWidth;
        //     IntervalsOfGroupedData interval;
        //     interval.lowerLimit = l;
        //     interval.upperLimit = u;
        //     interval.gap = 1;
           
        //     interval.midpoint = (l+u)/2;

        //     interval.frequency = 0;
        //     for (int i = 0; i < userData.size(); i++)
        //     {
        //         if (userData[i] >= l && userData[i] <= u)
        //         {
        //             interval.frequency++;
        //             interval.entries.push_back(userData[i]);
        //         }
        //     }
        //     Intervals.push_back(interval);
        //     l = u;
        // }