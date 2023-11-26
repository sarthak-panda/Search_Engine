#include <bits/stdc++.h>
#include <iostream>

using namespace std;
bool is_separator(char c)
{
    bool b = (c == '.' || c == ',' || c == '-' || c == ':' || c == '!' || c == '\"' || c == '\'' || c == '(' || c == ')' || c == '?' || c == '[' || c == ']' || c == ' ' || c == ';' || c == '@');
    return b;
}
int main()
{
    int book_code_max = -1;
    int page_no_max = -1;
    int para_no_max = -1;
    int sentence_no_max = -1;

    int num_books = 98;
    std::map<int, vector<int>> m;
    for (int i = 1; i <= num_books; i++)
    {

        // std::cout << "Inserting book " << i << std::endl;

        std::string filename = "mahatma-gandhi-collected-works-volume-";
        filename += to_string(i);
        filename += ".txt";

        std::ifstream inputFile(filename);

        if (!inputFile.is_open())
        {
            std::cerr << "Error: Unable to open the input file mahatma-gandhi." << std::endl;
            return 1;
        }

        std::string tuple;
        std::string sentence;

        while (std::getline(inputFile, tuple, ')') && std::getline(inputFile, sentence))
        {
            // Get a line in the sentence
            tuple += ')';
            int wordcount = 0;
            std::vector<int> metadata;
            std::istringstream iss(tuple);

            // Temporary variables for parsing
            std::string token;

            // Ignore the first character (the opening parenthesis)
            iss.ignore(1);

            // Parse and convert the elements to integers
            while (std::getline(iss, token, ','))
            {
                // Trim leading and trailing white spaces
                size_t start = token.find_first_not_of(" ");
                size_t end = token.find_last_not_of(" ");
                if (start != std::string::npos && end != std::string::npos)
                {
                    token = token.substr(start, end - start + 1);
                }

                // Check if the element is a number or a string
                if (token[0] == '\'')
                {
                    // Remove the single quotes and convert to integer
                    int num = std::stoi(token.substr(1, token.length() - 2));
                    metadata.push_back(num);
                }
                else
                {
                    // Convert the element to integer
                    int num = std::stoi(token);
                    metadata.push_back(num);
                }
            }
            for (int i = 0; i < sentence.length(); i++)
            {

                if (is_separator(sentence[i]))
                {
                    wordcount++;
                }
            }
            if (wordcount > 0)
            {
                wordcount--;
            }
            // Now we have the string in sentence
            // And the other info in metadata
            // Add to the dictionary
            // Insert in the qna_tool
            // cout << metadata[0] << " " << metadata[1] << " " << metadata[2] << " " << wordcount << endl;
            m[metadata[0]].push_back(metadata[1]);
            //  cout << metadata[0] << " " << metadata[1] << " " << metadata[2] << " " << wordcount << " " << m[make_tuple(metadata[0], metadata[1], metadata[2])] << endl;
            if (metadata[0] > book_code_max)
            {
                book_code_max = metadata[0];
            }
            if (metadata[1] > page_no_max)
            {
                page_no_max = metadata[1];
            }
            if (metadata[2] > para_no_max)
            {
                para_no_max = metadata[2];
            }
            if (metadata[3] > sentence_no_max)
            {
                sentence_no_max = metadata[3];
            }
        }

        inputFile.close();
    }
    int maxCount = -1;
    for (const auto &entry : m)
    {
        cout << entry.first << " " << entry.second.back() << endl;
        if (entry.second.back() > maxCount)
        {
            maxCount = entry.second.back();
        }
    }
    cout << maxCount << " "
         << "maxCount" << endl;
    cout << book_code_max << endl;
    cout << page_no_max << endl;
    cout << para_no_max << endl;
    cout << sentence_no_max << endl;

    return 0;
}