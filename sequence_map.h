// Shezan Alam

// References: Data Structures and Algorithm Analysis in C++ by Mark A. Weiss 
// References: Sven Dietrich CSCI 335 Slides


//SequenceMap class with big five, operator overloads, and merge function.
#include <string>
#include <vector>
#include <iostream> 


using namespace std; 

class SequenceMap
{
    public:
        //Big Five 
        SequenceMap() = default; // Default constructor 

        ~SequenceMap() = default; //Destructor 

        SequenceMap(const SequenceMap& rhs) = default; //Copy constructor 

        SequenceMap& operator=(const SequenceMap& rhs) = default; //Copy assignment 

        SequenceMap(SequenceMap&& rhs) = default; //Move constructor 

        SequenceMap& operator=(SequenceMap&& rhs) = default; //Move assignment

        /**
         * @brief Construct a new Sequence Map object
         * 
         * @param a_rec_seq : key for SequenceMap object
         * @param an_enz_acro : string of enzyme acronym to be added to vector
         * @post Constucts a new Sequence Map object with paramters 
         *         recognition sequence and enzyme acronym 
         */
        SequenceMap(const string& a_rec_seq, const string& an_enz_acro) 
        {
            recognition_sequence_ = a_rec_seq;
            enzyme_acronyms_.push_back(an_enz_acro);
        };

        /**
         * @brief Compares recoginition sequence lhs to recognition sequence rhs
         * @param rhs : SequenceMap object to be compared to 
         * @return true or false
         */
        bool operator<(const SequenceMap &rhs) const
        {
            return recognition_sequence_ < rhs.recognition_sequence_;
        };
     
        /**
         * @brief prints enyzyme acronyms vector
         * @param out 
         * @param sequence_map : SequenceMap object with enzyme acronyms to print 
         * @return std::ostream& 
         * @post prints enyzyme acronyms vector
         */
        friend std::ostream& operator<<(std::ostream& out, const SequenceMap& sequence_map) 
        {
            
            for(int i = 0; i < sequence_map.enzyme_acronyms_.size(); ++i){
                out << sequence_map.enzyme_acronyms_[i] << " ";
            }
            return out;
        }
        /**
         * @param other_sequence : SequenceMap object to be merged
         * @post appends other_sequence enzyme acronyms to lhs enzyme vector
         */
        void Merge(const SequenceMap &other_sequence)
        {
            for (const auto &i : other_sequence.enzyme_acronyms_)
            {
                enzyme_acronyms_.push_back(i);
            }
        };
    
    private:
        string recognition_sequence_;
        vector<string> enzyme_acronyms_; 
};

