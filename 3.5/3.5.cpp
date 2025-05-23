#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

class File {
protected:
    string filename;
public:
    File(const string& name) : filename(name) {
        cout << "[File] Created: " << filename << endl;
    }
    virtual ~File() {
        cout << "[File] Destroyed: " << filename << endl;
    }
    virtual void info() const {
        cout << "File: " << filename << endl;
    }
    friend istream& operator>>(istream& in, File& f) {
        cout << "Enter filename: ";
        in >> f.filename;
        return in;
    }
    friend ostream& operator<<(ostream& out, const File& f) {
        out << "Filename: " << f.filename;
        return out;
    }
};

class ReadableFile : virtual public File {
public:
    ReadableFile(const string& name) : File(name) {
        cout << "[ReadableFile] Created: " << filename << endl;
    }
    virtual ~ReadableFile() {
        cout << "[ReadableFile] Destroyed: " << filename << endl;
    }
    void read() {
        ifstream fin(filename);
        if (!fin) {
            cerr << "Error opening file for reading." << endl;
            return;
        }
        string line;
        while (getline(fin, line)) {
            cout << line << endl;
        }
        fin.close();
    }
};

class WritableFile : virtual public File {
public:
    WritableFile(const string& name) : File(name) {
        cout << "[WritableFile] Created: " << filename << endl;
    }
    virtual ~WritableFile() {
        cout << "[WritableFile] Destroyed: " << filename << endl;
    }
    void write(const string& data) {
        ofstream fout(filename, ios::app);
        if (!fout) {
            cerr << "Error opening file for writing." << endl;
            return;
        }
        fout << data << endl;
        fout.close();
    }
};

class ReadWriteFile : public ReadableFile, public WritableFile {
public:
    ReadWriteFile(const string& name)
        : File(name), ReadableFile(""), WritableFile("") {
        cout << "[ReadWriteFile] Created: " << filename << endl;
    }
    virtual ~ReadWriteFile() {
        cout << "[ReadWriteFile] Destroyed: " << filename << endl;
    }
    void info() const override {
        cout << "ReadWriteFile: " << filename << endl;
    }
};

// Тестова програма
int main() {
    cout << "=== Тест базового класу File ===" << endl;
    File f("base.txt");
    f.info();

    cout << "\n=== Тест ReadableFile ===" << endl;
    ReadableFile rf("input.txt");
    rf.read();

    cout << "\n=== Тест WritableFile ===" << endl;
    WritableFile wf("output.txt");
    wf.write("Це тестовий запис.");

    cout << "\n=== Тест ReadWriteFile ===" << endl;
    ReadWriteFile rwf("both.txt");
    rwf.write("Змішане використання: запис.");
    rwf.read();
    rwf.info();

    cout << "\n=== Тест введення з клавіатури ===" << endl;
    File inputFile("");
    cin >> inputFile;
    cout << inputFile << endl;

    cout << "\n=== Тест випадкових даних ===" << endl;
    int randID = rand() % 100;
    File randFile("rand_" + to_string(randID) + ".txt");
    randFile.info();

    return 0;
}
