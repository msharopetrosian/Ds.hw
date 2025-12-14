#include <iostream>
#include <stack>
using namespace std;

// Insert an element into a stack in descending order
void insertSorted(stack<int>& st, int x) {
    stack<int> temp;

    // Move smaller elements to temp
    while (!st.empty() && st.top() < x) {
        temp.push(st.top());
        st.pop();
    }

    // Insert the element
    st.push(x);

    // Restore elements
    while (!temp.empty()) {
        st.push(temp.top());
        temp.pop();
    }
}

// Merge two stacks into one pyramidal stack
stack<int> mergeStacks(stack<int>& s1, stack<int>& s2) {
    stack<int> result;

    while (!s1.empty()) {
        insertSorted(result, s1.top());
        s1.pop();
    }

    while (!s2.empty()) {
        insertSorted(result, s2.top());
        s2.pop();
    }

    return result;
}

int main() {
    stack<int> s1, s2;

    s1.push(3);
    s1.push(1);
    s1.push(7);

    s2.push(4);
    s2.push(9);
    s2.push(2);

    stack<int> merged = mergeStacks(s1, s2);

    cout << "Merged pyramidal stack (top to bottom):" << endl;
    while (!merged.empty()) {
        cout << merged.top() << " ";
        merged.pop();
    }

    return 0;
}
