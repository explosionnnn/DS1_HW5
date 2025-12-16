// 11327121 侯至謙 11327155 黃宇謙
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

struct Node {
    std::vector<int> number_list;
    int hp;
    Node *right;
    Node *left;
};

struct Statics {
    int num;
    std::string name;
    std::string type1;
    std::string type2;
    int total;
    int hp;
    int atk;
    int def;
    int sp_atk;
    int sp_def;
    int speed;
    int generation;
    std::string legendary;
};

struct Record1 {
    int num;
    std::string name;
    std::string type1;
    int total;
    int hp;
    int atk;
    int def;
};

class BinarySearchTree {
    private:
        Node* root;
    public:
        BinarySearchTree() {
            root = nullptr;
        }

        Node* top() {
            return root;
        }

        Node* right() {
            return root->right;
        }

        Node* left() {
            return root->left;
        }

        void set(Node* node) {
            this -> root = node;
        }

        bool empty() {
            return root == nullptr;
        }

        int height(Node* tree) {
            Node* cur = tree;
            if (cur == nullptr) {
                return 0;
            }
            int right = height(cur -> right);
            int left = height(cur -> left);
            return std::max(right, left) + 1;
        }

        Node* max(Node *tree) {
            if (tree == nullptr) {
                return tree;
            }
            while (tree -> right) {
                tree = tree -> right;
            }
            return tree;
        }
};

class System {
    private:
        std::vector<Statics> main_list;
        std::size_t size;
        BinarySearchTree root;
        int height;
    public:
        System() {
            size = 0;
            height = 0;
        }

        int binarySearch(int target) {
            int l = 0, r = main_list.size() - 1;

            while (l <= r) {
                int mid = l + (r - l) / 2;
                if (main_list[mid].num == target)
                    return mid;
                else if (main_list[mid].num < target)
                    l = mid + 1;
                else
                    r = mid - 1;
            }
            return -1;
        }

        Node* add(int num, int hp, Node *tree) {
            Node* cur = root.top();
            if (cur == nullptr) {
                Node* new_node = new Node;
                new_node -> hp = hp;
                new_node -> left = nullptr;
                new_node -> right = nullptr;
                new_node -> number_list.push_back(num);
                cur = new_node;
                return cur;
            } else if (cur -> hp < hp) {
                cur -> left = add(num, hp, cur -> left);
                return cur;
            } else if (cur -> hp > hp) {
                cur -> right = add(num, hp, cur -> right);
                return cur;
            } else if (cur -> hp == hp) {
                cur -> number_list.push_back(num);
                return cur;
            }
            return cur;
        }

        int findInRange(int lower, int upper, Node *tree, std::vector<int>& list) {
            Node *cur = tree;
            std::size_t count = 0;
            if (lower > cur -> hp) 
                count += findInRange(lower, upper, tree->left, list);
            if (lower <= cur -> hp && upper >= cur -> hp) {
                for (auto number : cur -> number_list) {
                    list.push_back(number);
                }
                count += cur -> number_list.size();
            }
            if (upper < cur -> hp)
                count += findInRange(lower, upper, tree->right, list);
            return count;
        }

        void Task1() {
            std::string prefix;
            std::cin >> prefix;
            if (!std::ifstream("input" + prefix + ".txt")) {
                std::cout << "File not found!\n";
                return;
            }
            IO::readFile(prefix, main_list);
            IO::printTask1(main_list);
        }

        void Task2(int num1, int num2) {
            std::vector<int> list;
            int index;
            Node* cur = root.top();
            if (num1 > num2) 
                std::swap(num1, num2);
            int count_visited = findInRange(num1, num2, cur, list);
            for (int i = 0; i < list.size(); i++) {
                index = binarySearch(list[i]);
                IO::printTask2(main_list[index]);
            }
        }
};

class IO {
    public:
        static void readFile(const std::string& prefix, std::vector<Statics>& list) {
            std::ifstream file("input" + prefix + ".txt");
            std::string header;
            std::getline(file, header);
            std::string line;
            while (std::getline(file, line)) {
                std::istringstream linestream(line);
                Statics data;
                std::string num, name, type1, type2, total, hp, atk, def, sp_atk, sp_def, speed, generation, legendary;
                linestream >> num >> name >> type1 >> type2;
                if (std::stoi(type2)) { // no type2 value -> total
                    total = type2;
                } else {
                    linestream >> total;
                }
                linestream >> hp >> atk >> def >> sp_atk >> sp_def >> speed >> generation >> legendary;
                data.num = std::stoi(num);
                data.name = name;
                data.type1 = type1;
                data.type2 = type2;
                data.total = std::stoi(total);
                data.hp = std::stoi(hp);
                data.atk = std::stoi(atk);
                data.def = std::stoi(def);
                data.sp_atk = std::stoi(sp_atk);
                data.sp_def = std::stoi(sp_def);
                data.speed = std::stoi(speed);
                data.generation = std::stoi(generation);
                data.legendary = legendary;
                list.push_back(data);
            }
        }

        static void printTask1(const std::vector<Statics>& list);
        static void printTask2(Statics data);
}; 