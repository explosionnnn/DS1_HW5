#include<iostream>
#include<vector>
#include<string>

struct Number {
    int num;
    int hp;
};

struct Bst {
    std::vector<Number> list;
    Bst *right;
    Bst *left;
};

struct Main {
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
    bool is_legend;
};

struct Rec1 {
    int num;
    std::string name;
    std::string type1;
    int total;
    int hp;
    int atk;
    int def;
}

class System {
    private:
        std::vector<Main> main_list;
        int main_list_size;
        Bst *tree;
        int tree_height;
    public:
        System() {
            main_list_size = 0;
            tree_height = 0;
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
            return -1; // 找不到
        }

        Bst* Add(int num, int hp, Bst *tree) {
            Bst *cur = tree;
            if (cur == nullptr) { // i.e., BST points to "empty"
                Bst *new_node = new Bst;
                Number n = {num, hp};
                new_node -> left = nullptr;
                new_node -> right = nullptr;
                new_node -> list.push_back(n);
                cur = new_node;
                return cur;
            } else if (cur -> list[0].hp < hp) {
                cur -> right = Add(num, hp, cur -> right); // store A on the right subtree
                return cur;
            } else if (cur -> list[0].hp > hp) {
                cur -> left = Add(num, hp, cur -> left);
                return cur;
            } else if (cur -> list[0].hp == hp) {
                Number n = {num, hp};
                cur -> list.push_back(n);
                return cur;
            }
            return cur;
        }

        int Height(Bst *tree) {
            Bst *cur = tree;
            if (cur == NULL) {
                return 0;
            }
            int right = Height(cur -> right);
            int left = Height(cur -> left);
            if (right > left) {
                return right+1;
            } else {
                return left+1;
            }
        }

        int FindInRange(int num1, int num2, Bst *tree, std::vector<int> &list) {
            Bst *cur = tree;
            int count = 0;
            int cur_hp = cur -> list[0].hp;

            if (num1 > cur_hp) {
                count += FindInRange(num1, num2, tree->left, list); //先找左
            }

            if (num1 <= cur_hp && num2 >= cur_hp) {
                for (int i = 0; i < cur -> list.size(); i++) {
                    list.push_back(cur -> list[0].num);
                }
            }

            if (num2 < cur_hp) {
                count += FindInRange(num1, num2, tree->right, list); //找右
            }

            return count;
        }

        void Task1() {
            ReadFile(); //havn't design
            main_list_size = main_list.size();
            for (int i = 0; i < main_list_size; i++) {
                tree = Add(main_list[i].num, main_list[i].hp, tree);
            }
            tree_height = Height(tree);
        }

        void Task2(int num1, int num2) {
            std::vector<int> list;
            int index;
            if (num1 > num2) {
                int tmp = num2;
                num2 = num1;
                num1 = tmp;
            }
            int count_visited = FindInRange(num1, num2, tree, list);
            for (int i = 0; i < list.size(); i++) {
                index = binarySearch(list[i]);
                PrintTask2(main_list[index]); //hasn't design
            }
        }
};
