# include <iostream>
using namespace std;

char* cpy(const char*); // returns a new heap allocated string copy

// input validation
void clearInput();
int readPositiveInt(const char*);
int readNonNegativeInt(const char*);
void readName(const char*, char*, int);

// required classes

class Spell {
    private:
        char* spellName;
        int power;
        int manaCost;
        int difficulty;
    public:
        Spell(); // default constructor
        Spell(char* , int, int, int); // parameterized constructor
        Spell(const Spell&);
        ~Spell(); // destructor

        // implementation
        void displaySpell();
        char* getName();
        Spell& operator=(const Spell&);
        Spell operator+(const Spell&);
        bool operator>(const Spell&);
        friend ostream& operator<<(ostream&, const Spell&);
};

Spell :: Spell()    {
    power = 0, manaCost = 0, difficulty = 0;
    spellName = cpy("Unknown");
}

Spell :: Spell(char* spell, int pow, int mana, int diff)    {
    power = pow, manaCost = mana, difficulty = diff;
    spellName = cpy(spell);
}

Spell :: Spell(const Spell& dummy)  {
    power = dummy.power;
    manaCost = dummy.manaCost;
    difficulty = dummy.difficulty;
    spellName = cpy(dummy.spellName);
}

Spell& Spell :: operator=(const Spell& dummy) {
    if (this == &dummy) return *this;
    delete[] spellName;
    spellName = cpy(dummy.spellName);
    power = dummy.power;
    manaCost = dummy.manaCost;
    difficulty = dummy.difficulty;
    return *this;
}

Spell Spell :: operator+(const Spell& dummy)    {

    Spell temp;

    // free constructor allocated memory
    delete[] temp.spellName;

    temp.spellName = cpy("FusionSpell");
    temp.power = this->power + dummy.power;
    temp.manaCost = this->manaCost +  dummy.manaCost;
    temp.difficulty = (this->difficulty + dummy.difficulty) / 2;

    if (temp.power > 100)   {
        delete[] temp.spellName;
        temp.spellName = cpy("UnstableMagic");
    }

    return temp;
}

bool Spell :: operator>(const Spell& dummy) {

    return this->power > dummy.power;
}

ostream& operator<<(ostream& cout, const Spell& dummy)    {

    cout << "Spell: " << dummy.spellName << " | Power:" 
    << dummy.power << " | Mana:" << dummy.manaCost 
    << " | Difficulty:" << dummy.difficulty << endl;

    return cout;
}

void Spell::displaySpell() {
    cout << "Spell: " << spellName << endl;
    cout << "Power: " << power << endl;
    cout << "Mana Cost: " << manaCost << endl;
    cout << "Difficulty: " << difficulty << endl;
}

char* Spell::getName() {
    return spellName;
}

Spell :: ~Spell()   {
    delete[] spellName;
}

class SpellBook {
    private:
        Spell* spells;
        int capacity;
        int totalSpells;
        char* ownerName;
    public:
        SpellBook(char*, int);
        ~SpellBook();

        // implementation
        void learnSpell(const Spell&);
        void displaySpellBook();

        // additional safety
        SpellBook(const SpellBook&);
        SpellBook& operator=(const SpellBook&);
};

SpellBook :: SpellBook(char* owner, int cap)    {
    ownerName = cpy(owner);
    capacity = cap;
    totalSpells = 0;
    spells = new Spell [capacity];
}

void SpellBook :: learnSpell(const Spell& s) {
    if (totalSpells >= capacity) {
        cout << "SpellBook is full!" << endl;
    } else {
        *(spells + totalSpells) = s;
        totalSpells++; 
    }
}

void SpellBook :: displaySpellBook() {
    // print owner name header
    cout << "--- " << ownerName << "\'s SpellBook ---" << endl;
    for (int i = 0; i < totalSpells; i++)   {
        cout << i + 1 << ". " << (*(spells + i)).getName() << endl;
    }
}

SpellBook :: SpellBook(const SpellBook& dummy) {
    capacity = dummy.capacity;
    totalSpells = dummy.totalSpells;
    ownerName = cpy(dummy.ownerName);
    spells = new Spell[capacity];
    for (int i = 0; i < totalSpells; i++)
        *(spells + i) = *(dummy.spells + i);
}

SpellBook& SpellBook :: operator=(const SpellBook& dummy) {
    if (this == &dummy) return *this;
    
    delete[] spells;
    delete[] ownerName;
    
    capacity = dummy.capacity;
    totalSpells = dummy.totalSpells;
    ownerName = cpy(dummy.ownerName);
    spells = new Spell[capacity];
    for (int i = 0; i < totalSpells; i++)
        *(spells + i) = *(dummy.spells + i);
    
    return *this;
}

SpellBook :: ~SpellBook()   {
    delete[] spells;
    delete[] ownerName;
}

int main() {
    // get spellbook owner and capacity
    char owner[100];
    // read owner name, reject empty or whitespace-only input
    readName("Enter owner name: ", owner, 100);
    // read capacity, reject non-numeric, zero, and negative values
    int cap = readPositiveInt("Enter spellbook capacity: ");
 
    SpellBook sb(owner, cap);

    int n = readPositiveInt("Enter number of spells to add: ");
 
    for (int i = 0; i < n; i++) {
        char name[100];

        readName("Enter spell name: ", name, 100);
        int pow  = readNonNegativeInt("Enter power: ");
        int mana = readNonNegativeInt("Enter mana cost: ");
        int diff = readNonNegativeInt("Enter difficulty: ");

        Spell s(name, pow, mana, diff);
        sb.learnSpell(s);
    }
 
    // combine first two spells
    if (n >= 2) {
        char name1[100], name2[100];
 
        cout << "\nEnter first spell to combine:" << endl;
        readName("Name: ", name1, 100);
        int pow1  = readNonNegativeInt("Power: ");
        int mana1 = readNonNegativeInt("Mana: ");
        int diff1 = readNonNegativeInt("Difficulty: ");
 
        cout << "Enter second spell to combine:" << endl;
        readName("Name: ", name2, 100);
        int pow2  = readNonNegativeInt("Power: ");
        int mana2 = readNonNegativeInt("Mana: ");
        int diff2 = readNonNegativeInt("Difficulty: ");
 
        Spell s1(name1, pow1, mana1, diff1);
        Spell s2(name2, pow2, mana2, diff2);
 
        // combine and learn
        Spell combo = s1 + s2;
        cout << "\nCombined spell:" << endl;
        combo.displaySpell();
        sb.learnSpell(combo);
 
        // compare
        if (s1 > s2)
            cout << name1 << " is stronger" << endl;
        else
            cout << name2 << " is stronger" << endl;
    }
 
    // display spellbook
    cout << endl;
    sb.displaySpellBook();
 
    return 0;
}

char* cpy (const char* src)   {
    int len = 0;
    while (src[len] != '\0')  len++;
    char* dest = new char[len + 1];
    for (int i = 0; i <= len; ++i) dest[i] = src[i];
    return dest;
}

void clearInput() {
    cin.clear();
    while (cin.get() != '\n');
}
 
int readPositiveInt(const char* prompt) {
    int val;
    cout << prompt;
    while (!(cin >> val) || val <= 0) {
        cout << "Invalid input. Enter a positive integer: ";
        clearInput();
    }
    clearInput();
    return val;
}

int readNonNegativeInt(const char* prompt) {
    int val;
    cout << prompt;
    while (!(cin >> val) || val < 0) {
        cout << "Invalid input. Enter a non-negative integer: ";
        clearInput();
    }
    clearInput();
    return val;
}

void readName(const char* prompt, char* buf, int size) {
    while (true) {
        cout << prompt;
        cin.getline(buf, size);
 
        if (cin.fail()) {
            clearInput();
            continue;
        }
 
        bool hasChar = false;
        for (int i = 0; buf[i] != '\0'; i++) {
            if (buf[i] != ' ' && buf[i] != '\t') {
                hasChar = true;
                break;
            }
        }
 
        if (!hasChar) {
            cout << "Name cannot be empty. Try again." << endl;
            continue;
        }
 
        break;
    }
}