// 11327121 侯至謙 11327155 黃宇謙
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <queue>
#include <utility>

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

class BinarySearchTree {
    private:
        Node* root;
    public:
        BinarySearchTree() {
            root = nullptr;
        }

        ~BinarySearchTree() {
            clear(root);
        }

        Node* top() const {
            return root;
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

        Node* add(int num, int hp, Node *tree) {
            if (tree == nullptr) {
                Node* new_node = new Node;
                new_node -> hp = hp;
                new_node -> left = nullptr;
                new_node -> right = nullptr;
                new_node -> number_list.push_back(num);
                tree = new_node;
                return tree;
            } else if (tree -> hp < hp) {
                tree -> right = add(num, hp, tree -> right);
                return tree;
            } else if (tree -> hp > hp) {
                tree -> left = add(num, hp, tree -> left);
                return tree;
            } else if (tree -> hp == hp) {
                tree -> number_list.push_back(num);
                return tree;
            }
            return tree;
        }

        Node* balance(std::vector<std::pair<int, std::vector<int>>>& inorder_nodes, int left, int right) {
            if (left > right) { return nullptr; }
            int mid = (left + right) / 2;
            Node* new_node = new Node;
            new_node -> hp = inorder_nodes[mid].first;
            new_node -> number_list = inorder_nodes[mid].second;
            new_node -> left = balance(inorder_nodes, left, mid - 1);
            new_node -> right = balance(inorder_nodes, mid + 1, right);
            return new_node;
        }

        int deleteMax(int &max_hp) {
            Node *cur = root;
            Node *parent = nullptr;
            if (!cur)
                return 0;
            while (cur -> right) {
                parent = cur;
                cur = cur -> right;
            }
            if (!parent) { //root
                if (cur -> left) {
                    root = cur -> left;
                    max_hp = cur -> left -> hp;
                } else {
                    root = nullptr;
                    max_hp = 0;
                }
            } else {
                parent->right = cur->left;
                if (parent -> right != nullptr) {
                    max_hp = parent -> right -> hp;
                } else {
                    max_hp = parent -> hp;
                }
            }

            int rec_hp = cur -> hp;
            delete cur;
            return rec_hp;
        }

        int deleteMin() {
            Node *cur = root;
            Node *parent = nullptr;
            if (!cur) {
                return 0;
            }
            while (cur -> left) {
                parent = cur;
                cur = cur -> left;
            }
            if (!parent) { // root
                if (cur -> right)
                    root = cur -> right;
                else
                    root = nullptr;
            } else {
                parent->left = cur->right;
            }
            int rec_hp = cur -> hp;
            delete cur;
            return rec_hp;
        }

        void clear(Node* tree) {
            if (tree) {
                clear(tree -> left);
                clear(tree -> right);
                delete tree;
            }
        }

        void inOrderHelper(Node* tree, std::vector<std::pair<int, std::vector<int>>>& result) {
            if (tree) {
                inOrderHelper(tree->left, result);
                result.push_back({tree->hp, tree->number_list});
                inOrderHelper(tree->right, result);
            }
        }

        void inOrder(Node* tree, std::vector<std::pair<int, std::vector<int>>> &result) {
            if (tree) {
                inOrderHelper(tree->left, result);
                result.push_back({tree->hp, tree->number_list});
                inOrderHelper(tree->right, result);
            }
            return;
        }
    };

class IO {
    public:
        static bool isNumber (const char& c) {
            if (c > '9' || c < '0') {
                return false;
            }
            return true;
        }


        static int binarySearch(const int &target, const std::vector<Statics> &main_list) {
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
            return -1; // 找不到
        }
        static void readFile(const std::string& prefix, std::vector<Statics>& list) {
            int count = 0;
            std::ifstream file("input" + prefix + ".txt");
            std::string header;
            std::getline(file, header);
            std::string num, name, type1, type2, total, hp, atk, def, sp_atk, sp_def, speed, generation, legendary;
            while (std::getline(file, num, '\t')) {
                Statics data;
                std::getline(file, name, '\t');
                std::getline(file, type1, '\t');
                std::getline(file, type2, '\t');
                if (isNumber(type2[0])) {
                    total = type2;
                    type2 = "";
                } else {
                    std::getline(file, total, '\t');
                }
                std::getline(file, hp, '\t');
                std::getline(file, atk, '\t');
                std::getline(file, def, '\t');
                std::getline(file, sp_atk, '\t');
                std::getline(file, sp_def, '\t');
                std::getline(file, speed, '\t');
                std::getline(file, generation, '\t');
                std::getline(file, legendary, '\n');
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

        static void printTask1(const std::vector<Statics>& list, const int &height) {
            int index = 1;
            std::cout << "\t#\tName" << std::setw(22) << "\tType 1"<< std::setw(8) << "\tHP\n";
            for (const auto& data : list) {
                std::cout << "[" << std::setw(3) << std::right << index++ << "]";
                std::cout << "\t" << data.num;                                  // num
                std::cout << "\t" << std::setw(20) << std::left << data.name;  // name (20)
                std::cout << "\t" << std::setw(10) << std::left << data.type1; // type1 (10)
                std::cout << "\t" << std::setw(6) << std::left << data.hp <<"\n";            // hp
            }
            std::cout << "HP tree height = " << height << "\n\n";
        }

        static void printTask2(const std::vector<int>& list, const std::vector<Statics>& main_list, const int &count_visited) {
            if (list.size() == 0) {
                std::cout << "No record was found in the specified range." << std::endl;
            } else {
                std::cout << "\t#"
                        << "\t" << "Name"
                        << "               \t" << "Type 1"
                        << "    \t" << "Total"
                        << "\t" << "HP"
                        << "\t" << "Attack"
                        << "\t" << "Defense"
                        << "\n";
            }

            for (int i = 0; i < list.size(); i++) {
                int idx = binarySearch(list[i], main_list);
                std::cout << "[" << std::setw(3) << std::right << i+1 << "]";
                std::cout << "\t" << main_list[idx].num;
                std::cout << "\t" << std::setw(20) << std::left << main_list[idx].name;
                std::cout << "\t" << std::setw(10) << std::left << main_list[idx].type1;
                std::cout << "\t" << std::setw(6) << std::left << main_list[idx].total;
                std::cout << "\t" << main_list[idx].hp;
                std::cout << "\t" << main_list[idx].atk;
                std::cout << "\t" << main_list[idx].def << "\n";
            }
            std::cout << "Number of visited nodes = " << count_visited << "\n\n";
        }

        static void printTask3(std::vector<Statics>& main_list, const int &rec_hp, const int &height) {
            int count = 1;
            std::cout << "\t#"
                    << "\t" << "Name"
                    << "               \t" << "Type 1"
                    << "    \t" << "Total"
                    << "\t" << "HP"
                    << "\t" << "Attack"
                    << "\t" << "Defense"
                    << "\t" << "Sp. Atk"
                    << "\t" << "Sp. Def"
                    << "\n";
            for (auto it = main_list.begin(); it != main_list.end();) {
                if (it -> hp == rec_hp) {
                    std::cout << "[" << std::setw(3) << std::right << count << "]";
                    std::cout << "\t" << it -> num;
                    std::cout << "\t" << std::setw(20) << std::left << it -> name;
                    std::cout << "\t" << std::setw(10) << std::left << it -> type1;
                    std::cout << "\t" << std::setw(6) << std::left << it -> total;
                    std::cout << "\t" << it -> hp;
                    std::cout << "\t" << it -> atk;
                    std::cout << "\t" << it -> def;
                    std::cout << "\t" << std::setw(6) << std::left << it -> sp_atk;
                    std::cout << "\t" << it -> sp_def << "\n";
                    it = main_list.erase(it); //回傳跳到下一個位置
                    count++;
                } else {
                    it++;
                }
            }
            std::cout << "HP tree height = " << height << "\n\n";
        }

        static void printTask4(const Node* tree) {
            if (!tree) return;
            std::queue<const Node*> q;
            q.push(tree);
            int level = 1;
            std::cout << "HP tree:" << std::endl;
            while (!q.empty()) {
                int size = q.size();
                std::cout << "<level " << level++ << ">";
                for (int i = 0; i < size; ++i) {
                    const Node* cur = q.front();
                    q.pop();
                    std::cout << " (" << cur->hp << ", ";
                    int last_value = cur->number_list.back();
                    for (const auto& value : cur->number_list) {
                        std::cout << value;
                        if (value != last_value) {
                            std::cout << "|";
                        }
                    }
                    std::cout << ")";
                    if (cur->left) { q.push(cur->left); }
                    if (cur->right) { q.push(cur->right); }
                }
                std::cout << "\n";
            }
        }

};

class System {
    private:
        std::vector<Statics> main_list;
        BinarySearchTree root;
        int height;
        bool deletemin;
        int max_hp;
    public:
        System() {
            height = 0;
            deletemin = true;
            max_hp = -1;
        }

        int findInRange(const int &lower, const int &upper, Node *tree, std::vector<int>& list) {
            if (!tree) {
                return 0;
            }
            Node *cur = tree;
            std::size_t count = 1;
            if (upper > cur -> hp)
                count += findInRange(lower, upper, tree->right, list);
            if (lower <= cur -> hp && upper >= cur -> hp) {
                for (auto number : cur -> number_list) {
                    list.push_back(number);
                }
            }
            if (lower < cur -> hp)
                count += findInRange(lower, upper, tree->left, list);
            return count;
        }

        void task1() {
            std::string prefix;
            while (true) {
                std::cout << "Input a file number [0: quit]: ";
                std::cin >> prefix;
                if (!std::ifstream("input" + prefix + ".txt")) {
                    std::cout << "\n### input" + prefix + ".txt does not exist! ###\n\n";
                    continue;
                } else {
                    break;
                }
            }
            deletemin = true;
            main_list.clear();
            root.clear(root.top());
            root.set(nullptr);
            IO::readFile(prefix, main_list);
            for (const auto& data : main_list) {
                root.set(root.add(data.num, data.hp, root.top()));
                if (data.hp > max_hp) {
                    max_hp = data.hp;
                }
            }
            IO::printTask1(main_list, root.height(root.top()));
        }

        void task2() {
            if (root.empty()) {
                std::cout << "----- Execute Mission 1 first! -----\n\n";
                return;
            }
            std::string input1, input2;
            int num1, num2;
            std::vector<int> list;
            int index;
            while (true) {
                std::cout << "Input a non-negative integer: \n";
                std::cin >> input1;
                try {
                    num1 = std::stoi(input1);
                    if (num1 < 0) {
                        throw num1;
                    }
                } catch (...) {
                    std::cout << "### It is NOT a non-negative integer. ###\nTry again: \n";
                    continue;
                }
                try {
                    if (num1 > 2*max_hp) {
                        throw num1;
                    }
                } catch (...) {
                    std::cout << "### It is NOT in [0," << 2*max_hp << "]. ###\nTry again: \n";
                    continue;
                }
                break;
            }
            while (true) {
                std::cout << "Input a non-negative integer: ";
                std::cin >> input2;
                try {
                    num2 = std::stoi(input2);
                    if (num2 < 0) {
                        throw num2;
                    }
                } catch (...) {
                    std::cout << "\n### It is NOT a non-negative integer. ###\nTry again: \n";
                    continue;
                }
                try {
                    if (num2 > 2*max_hp) {
                        throw num2;
                    }
                } catch (...) {
                    std::cout << "\n### It is NOT in [0," << 2*max_hp << "]. ###\nTry again: \n";
                    continue;
                }
                break;
            }
            Node* cur = root.top();
            if (num1 > num2)
                std::swap(num1, num2);
            int count_visited = findInRange(num1, num2, cur, list);
            IO::printTask2(list, main_list, count_visited);
        }

        void task3() {
            if (root.empty()) {
                std::cout << "----- Execute Mission 1 first! -----\n\n";
                return;
            }
            int rec_hp;
            if (deletemin) {
                rec_hp = root.deleteMin();
                deletemin = false;
            } else {
                rec_hp = root.deleteMax(max_hp);
                deletemin = true;
            }
            int height = root.height(root.top());
            IO::printTask3(main_list, rec_hp, height);
        }

        void task4() {
            if (root.empty()) {
                std::cout << "----- Execute Mission 1 first! -----\n\n";
                return;
            }
            std::vector<std::pair<int, std::vector<int>>> in_order_nodes;
            root.inOrder(root.top(), in_order_nodes);
            root.clear(root.top());
            root.set(root.balance(in_order_nodes, 0, in_order_nodes.size() - 1));
            IO::printTask4(root.top());
            deletemin = true;
            std::cout << "\n";
        }

        void run() {
            std::string task_input;
            int task_number;
            while (true) {
                std::cout << "*** (^_^) Data Structure (^o^) ***\n";
                std::cout << "** Binary Search Tree on Pokemon *\n";
                std::cout << "* 0. QUIT                        *\n";
                std::cout << "* 1. Read a file to build HP BST *\n";
                std::cout << "* 2. Range search on HP field    *\n";
                std::cout << "* 3. Delete the min on HP field  *\n";
                std::cout << "* 4. Rebuild the balanced HP BST *\n";
                std::cout << "**********************************\n";
                std::cout << "Input a choice(0, 1, 2, 3, 4): ";
                std::cin >> task_input;
                try {
                    task_number = std::stoi(task_input);
                } catch (...) {
                    std::cout << "\nCommand does not exist!\n\n";
                    continue;
                }
                if (task_number == 1) {
                    std::cout << "\n";
                    task1();
                } else if (task_number == 2) {
                    std::cout << "\n";
                    task2();
                } else if (task_number == 3) {
                    std::cout << "\n";
                    task3();
                } else if (task_number == 4) {
                    std::cout << "\n";
                    task4();
                } else if (task_number == 0) {
                    break;
                } else {
                    std::cout << "\nCommand does not exist!\n\n";
                }
            }
        }
};

int main () {
    System system;
    system.run();
    return 0;
}