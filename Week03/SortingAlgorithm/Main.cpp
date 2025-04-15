#include"Header.h"


int main(int argc, char* argv[]) {

    if (argc != 7) {
        cout << "Usage: ./main.exe -a <sort-type> -i <inputfile> -o <outputfile>" << endl;
        return 1;
    }

    string sortType, inputFile, outputFile;
    for (int i = 1; i < argc; i += 2) {
        string arg = argv[i];
        if (arg == "-a") sortType = argv[i + 1];
        else if (arg == "-i") inputFile = argv[i + 1];
        else if (arg == "-o") outputFile = argv[i + 1];
        else {
            cout << "Unknown option: " << arg << endl;
            return 1;
        }
    }

    ifstream fin(inputFile);
    if (!fin) {
        cout << "Cannot open input file: " << inputFile << endl;
        return 1;
    }

    int n;
    fin >> n;
    int* arr = new int[n];
    for (int i = 0; i < n; i++)
        fin >> arr[i];
    fin.close();


    Sort(arr, n, sortType); 

    ofstream fout(outputFile);
    fout << n << endl;
    for (int i = 0; i < n; i++)
        fout << arr[i] << " ";
    fout.close();

    cout << "Sorted using " << sortType << endl;
    cout << "Result saved to: " << outputFile << endl;

    delete[] arr;
    return 0;
}


