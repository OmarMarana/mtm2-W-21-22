// #include<vector>


// class BadInput
// {

// };

// template<class T>
// std::vector<T> slice(std::vector<T> vec, int start, int step, int stop)
// {
//     if(start < 0 || start > vec.size())
//     {
//         throw BadInput();
//     }
//     if(stop < 0 || stop > vec.size())
//     {
//         throw BadInput();
//     }
//     if(step <= 0)
//     {
//         throw BadInput();
//     }    

//     std::vector<T> new_vec;
//     for(int i = start ; i < stop ; i += step)
//     {
//         new_vec.push_back(vec[i]);
//     }
// }

