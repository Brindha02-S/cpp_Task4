#include <iostream>
#include <fstream>

using namespace std;

// Function to compress using Run-Length Encoding
string rle_compress(const string& data) {
    string compressed;
    int n = data.size();
    for (int i = 0; i < n; i++) {
        int count = 1;
        while (i < n - 1 && data[i] == data[i + 1]) {
            count++;
            i++;
        }
        compressed += data[i] + to_string(count);
    }
    return compressed;
}

// Function to decompress using Run-Length Encoding
string rle_decompress(const string& data) {
    string decompressed;
    int n = data.size();
    for (int i = 0; i < n; i++) {
        char ch = data[i];
        string countStr;
        while (i + 1 < n && isdigit(data[i + 1])) {
            countStr += data[i + 1];
            i++;
        }
        int count = stoi(countStr);
        decompressed.append(count, ch);
    }
    return decompressed;
}

// Function to handle file compression
void compress_file(const string& input_file, const string& output_file) {
    ifstream in(input_file, ios::binary);
    ofstream out(output_file, ios::binary);

    if (!in || !out) {
        cerr << "Error opening file!" << endl;
        return;
    }

    string data((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
    string compressed = rle_compress(data);
    out << compressed;

    cout << "Compression completed successfully!" << endl;
}

// Function to handle file decompression
void decompress_file(const string& input_file, const string& output_file) {
    ifstream in(input_file, ios::binary);
    ofstream out(output_file, ios::binary);

    if (!in || !out) {
        cerr << "Error opening file!" << endl;
        return;
    }

    string compressed((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
    string decompressed = rle_decompress(compressed);
    out << decompressed;

    cout << "Decompression completed successfully!" << endl;
}

int main() {
    string input_file = "input.txt";
    string compressed_file = "compressed.txt";
    string decompressed_file = "output.txt";

    cout << "Compressing..." << endl;
    compress_file(input_file, compressed_file);

    cout << "Decompressing..." << endl;
    decompress_file(compressed_file, decompressed_file);

    return 0;
}
