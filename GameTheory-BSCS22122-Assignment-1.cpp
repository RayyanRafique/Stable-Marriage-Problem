#include <iostream>
#include <string>
#include <fstream>
#include <vector>
int capacity = 5;

void initialize(
    std::vector<std::vector<std::string>>& menPref,
    std::vector<std::vector<std::string>>& womenPref,
    int MaleSize,
    int WomenSize
) 
{
    std::ifstream menFileIn("Men.txt");
    std::ifstream womenFileIn("Women.txt");

    for (int i = 0; i <= WomenSize-1; i++) {
        for (int j = 0; j <= MaleSize-1; j++) {
            womenFileIn >> womenPref[i][j];
        }
    }
    for (int i = 0; i <= MaleSize-1; i++) {
        for (int j = 0; j <= WomenSize-1; j++) {
            menFileIn >> menPref[i][j];
        }
    }
}

int menindex(std::string MaleName, int MaleSize, std::vector<std::string> men) {
    for (int i = 0; i <= MaleSize-1; i++) {
        if (men[i] == MaleName) {
            return i;
        }
    }
    return -1;
}

int womenindex(std::string WomenName,int WomenSize, std::vector<std::string> women) {
    for (int i = 0; i <= WomenSize-1; i++) {
        if (women[i] == WomenName) {
            return i;
        }
    }
    return -1;
}

bool ExtraPreference(std::string curPartner, std::string newPartner, int index, std::vector<std::vector<std::string>>& womenPref) {
    for (int i = 0; i < capacity; i++) {
        if (womenPref[index][i] == newPartner) {
            return true;
        }
        if (womenPref[index][i] == curPartner) {
            return false;
        }
    }
    return true;
}

void printCouples(std::vector<std::string> womenPartner, std::vector<std::string> women) {
    std::cout << std::endl;
    std::cout << "The Final Couples are: " << std::endl;
    for (int i = 0; i < capacity; i++) {
        std::cout << womenPartner[i] << "  <==>  " << women[i] << std::endl;
    }
    std::cout << std::endl;
}

void PrintMenPreferences(int MenSize, int WomenSize, const std::vector<std::vector<std::string>>& menPref) {
    std::cout << "Men's Preference List:" << std::endl;
    for (int i = 0; i < MenSize; i++) {
        std::cout << "M" << i + 1 << ": ";
        for (int j = 0; j < WomenSize; j++) {
            std::cout << menPref[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void PrintWomenPreferences(int MenSize, int WomenSize, const std::vector<std::vector<std::string>>& womenPref) {
    std::cout << "Women's Preference List:" << std::endl;
    for (int i = 0; i < WomenSize; i++) {
        std::cout << "W" << i + 1 << ": ";
        for (int j = 0; j < MenSize; j++) {
            std::cout << womenPref[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}




void proposeToWomen(int free, std::vector<bool>& menengaged,
    std::vector<std::string>& womenpartner, std::vector<std::string>& men,
    std::vector<std::string>& women, std::vector<std::vector<std::string>>& womenpref,
    std::vector<std::vector<std::string>>& menpref, int wsize, int msize)
{
    for (int i = 0; i < capacity && !menengaged[free]; i++) {
        int index = womenindex(menpref[free][i], wsize, women);
        if (womenpartner[index] == "") {
            womenpartner[index] = men[free];
            menengaged[free] = true;
        }
        else {
            std::string currentpartner = womenpartner[index];
            if (ExtraPreference(currentpartner, men[free], index, womenpref)) {
                womenpartner[index] = men[free];
                menengaged[free] = true;
                int curPartnerIndex = menindex(currentpartner, msize, men);
                if (curPartnerIndex != -1) {
                    menengaged[curPartnerIndex] = false;
                }
            } 
        }
    }
}

void StableMarriageAlgo(std::vector<bool>& menengaged, std::vector<std::string>& womenpartner,
    std::vector<std::string>& men, std::vector<std::string>& women,
    std::vector<std::vector<std::string>>& womenpref, std::vector<std::vector<std::string>>& menpref,
    int wsize, int msize)
{
    int engagedcount = 0;

    while (engagedcount < capacity) {
        int free;
        for (free = 0; free < capacity; free++) {
            if (!menengaged[free]) {
                break;
            }
        }
        proposeToWomen(free, menengaged, womenpartner, men, women, womenpref, menpref, wsize, msize);
        engagedcount++;
    }
}




int main() {
    std::cout << "\t\t\t\t       " << "STABLE MARRIAGE ALGORITHM BY GALE-SHAPLEY" << std::endl;
    int MenSize = 5; // Specify the number of men
    int WomenSize = 5; // Specify the number of women

    std::vector<std::vector<std::string>> menPref(MenSize, std::vector<std::string>(WomenSize));
    std::vector<std::vector<std::string>> womenPref(WomenSize, std::vector<std::string>(MenSize));
    std::vector<std::string> men(MenSize);
    std::vector<std::string> women(WomenSize);
    std::vector<std::string> womenPartner(WomenSize, ""); // Initialize all women as free
    std::vector<bool> menEngaged(MenSize, false); // Initialize all men as not engaged
    int engagedCount = 0;

    for (int i = 0; i < MenSize; i++) {
        men[i] = "M" + std::to_string(i + 1);
    }
    for (int i = 0; i < WomenSize; i++) {
        women[i] = "W" + std::to_string(i + 1);
    }

    initialize(menPref, womenPref, MenSize, WomenSize);
    std::cout << std::endl;

    PrintMenPreferences(MenSize, WomenSize, menPref);
    std::cout << std::endl;

    PrintWomenPreferences(MenSize ,WomenSize, womenPref);
    std::cout << std::endl;

    StableMarriageAlgo(menEngaged,womenPartner,men, women,womenPref, menPref,WomenSize, MenSize);

    printCouples(womenPartner, women);

    return 0;
}

