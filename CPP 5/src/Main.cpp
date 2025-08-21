#include <iostream>
#include <fstream>
#include <queue>
#include <stack>

//main, dpda, input, output

using namespace std;

//enum for input types so that I can use it in a switch case
enum startToSwitch {
    state,
    alphabeth,
    sAlphabeth,
    rule,
};

//changes strings to enum to use it in a switch case
startToSwitch hashit (string const& inString) {
    if (inString == "Q") return state;
    if (inString == "A") return alphabeth;
    if (inString == "Z") return sAlphabeth;
    if (inString == "T") return rule;
    return state;
}

//Checks if a string is in a vector because C++ hates variable strings
bool in_array(const string& value, vector<string> vector, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (value == vector[i])
        {
            return true;
        }
    }

    return false;
}

class Rule{
public:
    string State;
    string Read;
    string Pop;
    string Next;
    string Stack;
    Rule(string State, string Read, string Pop, string Next, string Stack){
        this->State = State;
        this->Read = Read;
        this->Pop = Pop;
        this->Next = Next;
        this->Stack = Stack;
    }
};

int main(int argc, char *argv[]) {
    //creating storage units

    vector<string> temp;
    string qTxt[2];
    string qText;
    string stateTemp;
    string ruleTemp[5];

    //Q holds all the states, A holds input alphabet, Z holds stack alphabet, T holds all the rules, In holds input, St holds stack
    vector<string> Q;
    vector<string> A;
    vector<string> Z;
    queue<Rule> T;
    queue<string> In;
    stack<string> St;

    //fStates holds all the states that would go to ACCEPT state, cState holds current state
    vector<string> fStates;
    string cState;

    ifstream file;
    ofstream output(argv[3], ofstream::out);
    string txtLine;

    //reading the DPDA file
    file.open (argv[1]);

    while(!file.eof()){
        getline(file,txtLine);
        string bigTxt[2];
        string txt;

        size_t start;
        size_t end = 0;

        //Splitting the line by ":"
        while ((start = txtLine.find_first_not_of(':', end)) != string::npos)
        {
            end = txtLine.find(':', start);
            bigTxt->append(txtLine.substr(start, end - start));
        }

        //Checking the first character to determine the input type
        switch (hashit(bigTxt[0])) {
            //If the first character is Q or determines states
            case state:
                qTxt->clear();
                qText = bigTxt[1];
                end = 0;

                //splitting the line by " => " qTxt[0] is all states, qTxt[1] is start and finish states
                while ((start = qText.find_first_not_of(" => ", end)) != string::npos)
                {
                    end = qText.find(" => ", start);
                    qTxt->append(qText.substr(start, end - start));
                }

                //Looking for all states
                qText = qTxt[0];
                end = 0;

                //Splitting by ","
                while ((start = qText.find_first_not_of(',', end)) != string::npos)
                {
                    end = qText.find(',', start);
                    Q.push_back(qText.substr(start, end - start));
                }

                //Looking for start and final states
                qText = qTxt[1];
                end = 0;

                //Clearing the temp vector before using
                temp.clear();

                //Splitting by ","
                while ((start = qText.find_first_not_of(',', end)) != string::npos)
                {
                    end = qText.find(',', start);
                    temp.push_back(qText.substr(start, end - start));
                }

                //Looking for '(' or '[' in the states
                for (auto & i : temp){
                    stateTemp = i;
                    string tempState = stateTemp.substr(1, stateTemp.size() - 2);
                    //We're checking if that state is in the state list
                    if (!in_array(tempState, Q, Q.size())){
                        if (stateTemp[0] == '('){
                            if (cState.empty()){
                                cState = tempState;
                            } else {
                                output << "Error [1]:DPDA description is invalid!" << endl;
                                return 0;
                            }
                        } else if (stateTemp[0] == '['){
                            fStates.push_back(tempState);
                        }
                    } else {
                        output << "Error [1]:DPDA description is invalid!" << endl;
                        return 0;
                    }
                }
                break;

            case alphabeth:
                qText = bigTxt[1];
                end = 0;

                //Splitting by ","
                while ((start = qText.find_first_not_of(',', end)) != string::npos)
                {
                    end = qText.find(',', start);
                    stateTemp = (qText.substr(start, end - start));
                    //We're checking if that char is already in the list
                    if (!in_array(stateTemp, A, A.size())){
                        A.push_back(stateTemp);
                    } else {
                        output << "Error [1]:DPDA description is invalid!" << endl;
                        return 0;
                    }
                    //We're adding e manually just in case
                    A.emplace_back("e");
                }
                break;

            case sAlphabeth:
                qText = bigTxt[1];
                end = 0;

                //Splitting by ","
                while ((start = qText.find_first_not_of(',', end)) != string::npos)
                {
                    end = qText.find(',', start);
                    stateTemp = (qText.substr(start, end - start));
                    //We're checking if that char is already in the list
                    if (!in_array(stateTemp, Z, Z.size())){
                        Z.push_back(stateTemp);
                    } else {
                        output << "Error [1]:DPDA description is invalid!" << endl;
                        return 0;
                    }
                    //We're adding e manually just in case
                    Z.emplace_back("e");
                }
                break;

            case rule:
                //State, Read, Pop ,Next, Push
                ruleTemp->clear();
                //Splitting by "," and everything to a temporary array
                while ((start = qText.find_first_not_of(',', end)) != string::npos) {
                    end = qText.find(',', start);
                    ruleTemp->append(qText.substr(start, end - start));

                    //Controlling if State is in Q array
                    if(!in_array(ruleTemp[0], Q, Q.size())){
                        output << "Error [1]:DPDA description is invalid!" << endl;
                        return 0;
                    }

                    //Controlling if Read is in A array
                    if(!in_array(ruleTemp[1], A, A.size())){
                        output << "Error [1]:DPDA description is invalid!" << endl;
                        return 0;
                    }

                    //Controlling if Pop is in Z array
                    if(!in_array(ruleTemp[2], Z, Z.size())){
                        output << "Error [1]:DPDA description is invalid!" << endl;
                        return 0;
                    }

                    //Controlling if Next is in Q array
                    if(!in_array(ruleTemp[3], Q, Q.size())){
                        output << "Error [1]:DPDA description is invalid!" << endl;
                        return 0;
                    }

                    //Controlling if Push is in Z array
                    if(!in_array(ruleTemp[4], Z, Z.size())){
                        output << "Error [1]:DPDA description is invalid!" << endl;
                        return 0;
                    }
                    T.push(Rule(ruleTemp[0], ruleTemp[1], ruleTemp[2], ruleTemp[3], ruleTemp[4]));
                }
                break;
            default:
                output << "Error [1]:DPDA description is invalid!" << endl;
                return 0;
        }
    }

    file.close();

    //reading the input file and doing the transitioning
    file.open (argv[2]);
    while(!file.eof()){
        getline(file,txtLine);
        string txt;

        //This clears Input queue and Stack stack
        queue<string> emptyI;
        stack<string> emptyS;
        swap(In, emptyI);
        swap(St, emptyS);

        size_t start;
        size_t end = 0;

        //Splitting the line by ","
        while ((start = txtLine.find_first_not_of(',', end)) != string::npos)
        {
            end = txtLine.find(',', start);
            txt = txtLine.substr(start, end - start);
            //checking if the input is in the alphabet
            if(!in_array(txt, A, A.size())){
                output << "Error [2]:Input is invalid!" << endl;
                return 0;
            }
            In.push(txt);
        }
        //This is our ACCEPT conditions
        stack<string> A1;
        A1.push("&");
        stack<string> A2;
        A2.push("&");
        A2.push("&");
        bool outputON = true;
        while(outputON != false){
            //Copying our rules to temporary queue
            queue<Rule> R = T;
            //This checks if Rule Queue is empty
            if(R.empty()){
                //This checks if Input is empty
                if(In.empty()){
                    if(!in_array(cState, fStates, fStates.size())){
                        if(St.empty()||St == A1||St == A2){
                            output << "ACCEPT" << endl << endl;
                            outputON = false;
                        } else{
                            output << "REJECT" << endl << endl;
                            outputON = false;
                        }
                    } else{
                        output << "REJECT" << endl << endl;
                        outputON = false;
                    }
                } else{
                    output << "REJECT" << endl << endl;
                    outputON = false;
                }
            } else{
                output << "REJECT" << endl << endl;
                outputON = false;
            }
            //This if checks RULES
            if(cState == R.front().State && R.front().Read == In.front() && R.front().Pop == St.top()) {
                //CHANGE INPUT, POP IT, CHANGE STATE, PUSH IT
                In.pop();
                St.pop();
                cState = R.front().Next;
                if(R.front().Stack == "e"){
                    continue;
                } else {
                    St.push(R.front().Stack);
                }

                //OUTPUT
                output << R.front().State << "," << R.front().Read << "," << R.front().Pop << " => " <<
                        R.front().Next << "," << R.front().Stack << " [STACK]:";
                stack<string> tempSt = St;
                output << tempSt.top();
                tempSt.pop();
                while (!tempSt.empty()) {
                    cout << ',' << tempSt.top();
                    tempSt.pop();
                }
                output << endl;
            } else if(cState == R.front().State && R.front().Read == In.front() && R.front().Pop == "e") {
                //CHANGE INPUT, CHANGE STATE, PUSH IT
                In.pop();
                cState = R.front().Next;
                if(R.front().Stack == "e"){
                    continue;
                } else {
                    St.push(R.front().Stack);
                }

                //OUTPUT
                output << R.front().State << "," << R.front().Read << "," << R.front().Pop << " => " <<
                       R.front().Next << "," << R.front().Stack << " [STACK]:";
                stack<string> tempSt = St;
                output << tempSt.top();
                tempSt.pop();
                while (!tempSt.empty()) {
                    cout << ',' << tempSt.top();
                    tempSt.pop();
                }
                output << endl;
            } else if(cState == R.front().State && R.front().Read == "e" && R.front().Pop == St.top()) {
                //POP IT, CHANGE STATE, PUSH IT
                St.pop();
                cState = R.front().Next;
                if(R.front().Stack == "e"){
                    continue;
                } else {
                    St.push(R.front().Stack);
                }

                //OUTPUT
                output << R.front().State << "," << R.front().Read << "," << R.front().Pop << " => " <<
                       R.front().Next << "," << R.front().Stack << " [STACK]:";
                stack<string> tempSt = St;
                output << tempSt.top();
                tempSt.pop();
                while (!tempSt.empty()) {
                    cout << ',' << tempSt.top();
                    tempSt.pop();
                }
                output << endl;
            } else if(cState == R.front().State && R.front().Read == "e" && R.front().Pop == St.top()) {
                //CHANGE STATE, PUSH IT
                cState = R.front().Next;
                if(R.front().Stack == "e"){
                    continue;
                } else {
                    St.push(R.front().Stack);
                }

                //OUTPUT
                output << R.front().State << "," << R.front().Read << "," << R.front().Pop << " => " <<
                       R.front().Next << "," << R.front().Stack << " [STACK]:";
                stack<string> tempSt = St;
                output << tempSt.top();
                tempSt.pop();
                while (!tempSt.empty()) {
                    cout << ',' << tempSt.top();
                    tempSt.pop();
                }
                output << endl;
            } else {
                R.pop();
            }
        }

    }

    return 0;
}
