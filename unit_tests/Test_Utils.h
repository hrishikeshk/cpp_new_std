
template <typename T, typename Func>
bool compare(const T& actual, const T& correct, int& test_number){

        bool is_correct = Func(actual, correct);
        if(is_correct){
                return true;
        }
        return false;
}

