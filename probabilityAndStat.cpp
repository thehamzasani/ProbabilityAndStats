#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
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
    float x;
    int frequency;
    float gap;
    float midpoint;
    vector<float> entries;
};

class TakingData{
public:
    vector<float> data = {
        106, 107, 76, 82, 109, 107, 115, 93, 187, 95, 123, 125,
        111, 92, 86, 70, 126, 68, 130, 129, 139, 119, 115, 128,
        100, 186, 84, 99, 113, 204, 111, 141, 136, 123, 90, 115,
        98, 110, 78, 185, 162, 178, 140, 152, 173, 146, 158, 194,
        148, 90, 107, 181, 131, 75, 184, 104, 110, 80, 118, 82};
    // vector<float> data = {15, 18, 21, 25, 27, 33, 36, 42, 48, 52};
    vector<IntervalsOfGroupedData> Intervals;
    vector<float> userData;

    int numberOfIntervals = 7;
    TakingData(int numberOfIntervals)
    {
        this->numberOfIntervals = numberOfIntervals;
    };
    TakingData()
    {
        
    };

    void makingIntervals(vector<float>& data)
    {
        // cout << "Enter number of intervals you want to make : ";
        // cin >> numberOfIntervals;
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
            for (int j = 0; j < data.size(); j++)
            {
                if (data[j] >= l && data[j] <= u)
                {
                    interval.frequency++;
                    interval.entries.push_back(data[j]);
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

    void takingGroupedData(){
        Intervals.clear();
        userData.clear();
        int amount;
        cout << "Enter the amount of data : ";
        cin >> amount;
        cout << "How many intervals do you want to make : ";
        cin >> numberOfIntervals;
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

    void takingUngroupData(){
        userData.clear();
        int amount;
        cout << "Enter the amount of data : ";
        cin >> amount;
        for (int i = 0; i < amount; i++)
        {
            float value;
            cout << "Enter the value of element " << i+1 << " : ";
            cin >> value;
            userData.push_back(value);
        }
        
    }
};

class Formulas : public TakingData{
    public: 
    float meanOfUngroupedData(){

        takingUngroupData();
      
        float sum=0;
        for (int i = 0; i < userData.size(); i++)
        {
            sum = sum + userData[i];
        }
        return sum/userData.size();  
    }

    float meanOfGroupedData(){
        takingGroupedData();
        // defaultData();
        float x = 0,fx = 0,f = 0;
        for (int i = 0; i < Intervals.size(); i++)
        {
            x = (Intervals[i].upperLimit + Intervals[i].lowerLimit)/2;
            fx += Intervals[i].frequency * x;
            f += Intervals[i].frequency;
        }
        return fx/f;
    };

    float medianOfUngroupedData(){
        takingUngroupData();
        sort(userData.begin(), userData.end());
        int n=userData.size();
        if (n%2==0)
        {
            return (userData[n/2 - 1] + userData[n/2]) / 2;
        }
        else
        {
            return userData[n/2];
        }
    }

    float medianOfGroupedData(){
        takingGroupedData();
        float ans;
        int sumOfCF=0;
       
        vector<int> commFreArray;
        for (int i = 0; i < Intervals.size(); i++)
        {
            sumOfCF += Intervals[i].frequency;
            commFreArray.push_back(sumOfCF);
        }
        float medianInterval = sumOfCF/2;
        float medianIntervalIndex;
        for (int i = 0; i < commFreArray.size(); i++)
        {
            if (commFreArray[i]>=medianInterval)
            {
                medianIntervalIndex = i;
                break;
            }
        }
        float L,N,F,f,h;

        f = Intervals[medianIntervalIndex].frequency;
        L = Intervals[medianIntervalIndex].lowerLimit;
        h = Intervals[medianIntervalIndex].upperLimit - Intervals[medianIntervalIndex].lowerLimit + 1;
        N = sumOfCF;
        F = (medianIntervalIndex==0 )? 0 : commFreArray[medianIntervalIndex-1];
        
        return L + ((N/2.0 - F) / f) * h;
    }

    float modeOfUngroupedData(){
        takingUngroupData();
        sort(userData.begin(), userData.end());
        int mode = 0;
        int currentCount = 1;
        int maxCount = 1;

        for (int i = 0; i < userData.size(); i++)
        {
            if (userData[i]==userData[i-1])
            {
                currentCount++;
            }
            else
            {
                currentCount = 1;
            }

            if (currentCount>maxCount)
            {
                maxCount=currentCount;
                mode= userData[i];
            }
        };
        return mode;
    }

    float modeOfGroupedData(){
        takingGroupedData();
        int L;
        int f0;
        int f1;
        int f2;
        int h;
        int modalClassIndex;
        f1 = Intervals[0].frequency;
        for (int i = 0; i < Intervals.size(); i++)
        {
            if (Intervals[i].frequency > f1)
            {   
                modalClassIndex = i;
                f0 = modalClassIndex==0 ? 0 : Intervals[i-1].frequency;
                f1 = Intervals[i].frequency;
                f2 = modalClassIndex==Intervals.size()-1 ? 0 : Intervals[i+1].frequency;
            }
            
        }
        h = Intervals[modalClassIndex].upperLimit - Intervals[modalClassIndex].lowerLimit + 1;
        L = Intervals[modalClassIndex].lowerLimit;
        
        return L + ((f1 - f0)/((2*f1)-f0-f2)) * h;

    };
};


int main()
{   
    int totalIntervals;
    int choice;
    
    while (true)
    {
        cout << "0) To exit Program" << endl;
        cout << "1) Find Mean (Arithmetic Mean)" << endl;
        cout << "2) Find Median" << endl;
        cout << "3) Find Mode" << endl;
        cout << "4) Find Geometric Mean" << endl;
        cout << "5) Built Frequency Distribution Table" << endl;
        cout << "Enter your choice : ";
        cin >> choice;
        if (choice==1)
        {
            cout << "-------------------------------------------------------------------------------" << endl;
            cout << "1) Grouped Data   | (Σ(fi * xi)) / Σfi" << endl;
            cout << "2) Ungrouped Data | sum / n" << endl;
            cout << "Enter your choice : ";
            cin >> choice;
            if (choice==1)
            {
                float mean;
                Formulas f;
                // mean = f.meanOfGroupedData();
                // cout << "Mean : " << mean << endl;

                mean = f.meanOfGroupedData();
                f.display();
                cout << "-------------------------------------------------------------------------------" << endl;
                cout << "Mean : " << mean << endl;
            }
            else if (choice==2)
            {
                float mean;
                Formulas f;
                mean = f.meanOfUngroupedData();
                f.display();
                cout << "-------------------------------------------------------------------------------" << endl;
                cout << "Mean : " << mean << endl;
            }
            else if (choice==0)
            {
                cout << "Program exit kita ja reha hai sukriya program run karen da"<< endl;
                return false;
            }
            else
            {
                cout << "Bhaijan vek ke choice enter kero";
            }
        }
        else if (choice==2)
        {
            cout << "1) Grouped Data   | L+(f2N​−F​)×h" << endl;
            cout << "2) Ungrouped Data | n/2" << endl;
            cout << "Enter your choice : ";
            cin >> choice;
            if (choice==1)
            {
                int median;
                Formulas f;   
                median = f.medianOfGroupedData();
                f.display();
                cout << "-------------------------------------------------------------------------------" << endl;
                cout << "Median : " << median << endl;
            }
            else if (choice==2)
            {
                int median;
                Formulas f;   
                median = f.medianOfUngroupedData();
                cout << "-------------------------------------------------------------------------------" << endl;
                cout << "Median : " << median <<  endl;
            }
            else if (choice==0)
            {
                cout << "Program exit kita ja reha hai sukriya program run karen da"<< endl;
                return false;
            }
            else
            {
                cout << "Bhaijan vek ke choice enter kero";
            }
        }
        else if (choice==3)
        {
            cout << "1) Grouped Data   | L+(2f1​−f0​−f2​f1​−f0​​)×h" << endl;
            cout << "2) Ungrouped Data | most occuring value" << endl;
            cout << "Enter your choice : ";
            cin >> choice;
            if (choice==1)
            {
                int mode;
                Formulas f;  
                mode = f.modeOfGroupedData();
                f.display();
                cout << "Mode : " << mode << endl;
            }
            else if (choice==2)
            {
                int mode;
                Formulas f;
                mode = f.modeOfUngroupedData();
                cout << "Mode : " << mode << endl;            
            }
            
            

        }
        else if (choice==4)
        {
            
        }
        
        
    }
    

    

    return 0;
}

/*
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

        // ----------------------------------
        // cout << "1) Default Data" <<  endl;
        // cout << "2) Input Data" << endl;
        // cout << "Enter your choice : ";
        // cin >> choice;
        
        // if (choice == 1)
        // {
        //     TakingData f(totalIntervals);
        //     f.defaultData();
        //     f.display();
        
        // }
        // else if (choice == 2)
        // {
        //     cout << "How many intervals of data do you want to make? : ";
        //     cin >> totalIntervals;
        //     TakingData f(totalIntervals);
        //     f.userInputData();
        //     f.display();
        // }
        // else if(choice == 0){
        //     cout << "Khuda Hafiz Program changa lagya te review ker deyo hamza nu" << endl;
        //     return false;
        // }
        // else
        // {
        //     cout << "vekh ke input ker choice vicho!!!";
        //     continue;
        // }
        */