#ifndef Matrix_H
#define Matrix_H
#include "Auxiliaries.h"
#include <iostream>
#include <string>
#include <cassert>
#include "Exceptions.h"

namespace mtm {
    /** class Matrix - implements a matrix container for objects of type T.
    * general assumptions on type T:
    * default c'tor, = operator, copy c'tor, d'tor.
    * function specific assumptions are listed per each function
    */
    template <class T>
    class Matrix{
        /** dimensions: the dimensions of the Matrix
        *   data: all the Matrix objects
        * */
        mtm::Dimensions dimensions;
        T* data;



        /** verifyIndex:   Checks if the index is a legal index.
        * */
        void verifyIndex(const int row, const int col) const;

        /** verifyDimensions:   Checks if the dimensions are legal dimensions (bigger then zero).
        * */
        static void verifyDimensions(const Dimensions dimensions);




        public:
        class iterator;

        /** iterator begin:   Creates a new iterator for the current Matrix
        * */
        iterator begin();

        /** iterator end:   Creates a iterator which is the end of the current Matrix
        * */
        iterator end();
        class const_iterator;
        
        /** const_iterator begin:   Creates a new const_iterator for the current const Matrix
        * */
        const_iterator begin() const;
        
        /** const_iterator end:   Creates a const_iterator is the end of the current const Matrix
        * */
        const_iterator end() const;



        
        /** AccessIllegalElement:   Exception thrown when trying to access an illegal element in the Matrix 
        * */
        class AccessIllegalElement : public mtm::Exception{
                std::string error_string;
                public:
                AccessIllegalElement(): error_string("Mtm matrix error: An attempt to access an illegal element"){}
                const char* what() const noexcept;
        };

        /** IllegalInitialization:   Exception thrown when trying to create a Matrix with illegal dimensions 
        * */
        class IllegalInitialization : public mtm::Exception{
            std::string error_string;
            public:
            IllegalInitialization(): error_string("Mtm matrix error: Illegal initialization values"){}
            const char* what() const noexcept;
        };
        
        /** DimensionMismatch:   Exception thrown when trying to operate on two Matrices with different dimensions 
        * */
        class DimensionMismatch : public mtm::Exception{
            std::string error_string;
            mtm::Dimensions dimensions_a;
            mtm::Dimensions dimensions_b;
            public:
            DimensionMismatch(Dimensions dimensions_a,Dimensions dimensions_b) : 
                                         dimensions_a(dimensions_a),dimensions_b(dimensions_b),
                                         error_string("Mtm matrix error: Dimension mismatch: " +
                                         dimensions_a.toString() + " " + dimensions_b.toString()) {};
            const char* what() const noexcept;
        };
        


        
        /** Matrix C'tor:   Creates a Matrix in the dimensions given with value given in each entry.
        *                  If no value was given, each entry is constructed with the default T C'tor
        * @assumptions: default c'tor for T, = operator for T
        * */
        Matrix(const mtm::Dimensions dimensions,const T value = T());

        /** Matrix Copy C'tor:  Creates a Matrix with the same values as the Matrix given
        * @assumptions: = operator for T
        * */
        Matrix(const Matrix& matrix);

        /** Diagonal:   Creates a Diagonal Matrix in the dimensions given, with given value in the diagonal
        * @assumptions: default c'tor for T, = operator for T
        * */
        static Matrix Diagonal(const int dimension,const T value);

        /** =(Matrix) operator:   Change current Matrix to be equivalent to the given Matrix.
        * @assumptions:  = operator for T
        * */
        Matrix& operator=(const Matrix& matrix);

        /** - operator:     Creates a Matrix equivalent to the given Matrix, 
         *                  with '-' operator applied on each entry.
        * @assumptions:   - operator for T, = operator for T
        * */
        Matrix operator-() const;
        
        /** height:     Returns the number of rows in the Matrix, 
        * */
        int height() const;

        /** width:     Returns the number of columns in the Matrix, 
        * */
        int width() const;
        
        /** size:     Returns the number of elements in the Matrix, 
        * */
        int size() const;
        
        /** Transpose: returns a transposed matrix.
        * @assumptions: = operator for T, calling Matrix<T> c'tor - default c'tor for T, and = operator for T
        * */
        Matrix transpose() const;

        /** () operator: returns a reference to an object in the matrix in the given row and column.
        * @assumptions:  = operator for T, calling Matrix<T> c'tor - default c'tor for T, and = operator for T; 
        * */
        T& operator()(const int row, const int col);

        /** () operator: returns a reference to an object in a const matrix in the given row and column.
        * @assumptions: none
        * */
        const T& operator()(const int row, const int col) const; 
 
        /** += operator: adds an object of type T to each matrix entry
        * @assumptions: +,= operators for T, calling Matrix<T> c'tor - default c'tor for T, and = operator for T
        * */
        Matrix& operator+=(const T object);
        
        /** apply: creates a new matrix - each entry contains the value after application of the given action
        * @assumptions: calling Matrix<T> c'tor - default c'tor for T, and = operator for T
        * */
        template<class action>
        Matrix<T> apply(action apply_action) const;
             
        /** Matrix Destructor: frees the data stored in the matrix and destroys the matrix.
        * @assumptions: destructor for T 
        * */
        ~Matrix();
   
    };
    
    /** << operator: returns reference to ostream in order to print the Matrix
        * @assumptions: = calling printMatrix - assuming that std::to_string can be called for T
    * */
    template <class T>
    std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix);

    /** + operator: returns a new matrix that contains the sum of 2 given matrices
        * @assumptions: +,= operators for T, calling Matrix<T> c'tor - default c'tor for T, and = operator for T
    * */
    template <class T>
    Matrix<T> operator+(const Matrix<T>& matrix_a, const Matrix<T>& matrix_b);

    /** + operator: returns a new matrix that contains the addition of the object (on the left) to the given matrix (on the right)
        * @assumptions: calling Matrix<T> c'tor - default c'tor for T, and = operator for T; calling + operator for 2 matrices - +
        * ,= operators for T
    * */
    template <class T>
    Matrix<T> operator+(const T object, const Matrix<T>& matrix);

    /** + operator: returns a new matrix that contains the addition of the object (on the right) to the given matrix (on the left)
        * @assumptions: calling Matrix<T> c'tor - default c'tor for T, and = operator for T; calling += operator - +,= operators for T
    * */
    template <class T>
    Matrix<T> operator+(const Matrix<T>& matrix, const T object);

    /** - operator: returns a new matrix that contains the subtraction of the right matrix from the left matrix
        * @assumptions: -,= operators for T, calling Matrix<T> c'tor - default c'tor for T
    * */
    template <class T>
    Matrix<T> operator-(const Matrix<T>& matrix_a, const Matrix<T>& matrix_b);

    /** (Matrix)>(T) operator:  Returns a Matrix<bool> with true in the entries where each entry 
    *                           is small or equal to object , and false otherwise
    * @assumptions:  <,== operator for T
    * */
    template <class T>
    Matrix<bool> operator<=(const Matrix<T>& matrix, const T object);

    /** (Matrix)<(T) operator:  Returns a Matrix<bool> with true in the entries where each entry 
    *                           is smaller then the object (determined by < operator on T), and false otherwise
    * @assumptions:  < operator for T
    * */
    template <class T>
    Matrix<bool> operator<(const Matrix<T>& matrix, const T object);

    /** (Matrix)>(T) operator:  Returns a Matrix<bool> with true in the entries where each entry 
    *                           is bigger then the object, and false otherwise
    * @assumptions:  <= operator for T
    * */
    template <class T>
    Matrix<bool> operator>(const Matrix<T>& matrix, const T object);

    /** (Matrix)>=(T) operator:  Returns a Matrix<bool> with true in the entries where each entry 
    *                            is bigger or equal to object (determined by >= operator on T), and false otherwise
    * @assumptions:   -, <= operator for T
    * */
    template <class T>
    Matrix<bool> operator>=(const Matrix<T>& matrix, const T object);

    /** (Matrix)==(T) operator:  Returns a Matrix<bool> with true in the entries where each entry 
    *                            is equivalent to object (determined by == operator on T), and false otherwise
    * @assumptions:  == operator for T
    * */
    template <class T>
    Matrix<bool> operator==(const Matrix<T>& matrix, const T object);

    /** (Matrix)!=(T) operator:  Returns a Matrix<bool> with true in the entries where each entry 
    *                            is not equivalent to object , and false otherwise
    * @assumptions:  == operator for T
    * */
    template <class T>
    Matrix<bool> operator!=(const Matrix<T>& matrix, const T object);

    /** all: returns true if all the elements in the Matrix is equivalent to true after boolean conversion
    * @assumptions:  bool convertor for T
    * */
    template <class T>
    bool all(const Matrix<T>& matrix);
    
    /** any: returns true if there is any element in the Matrix that is equivalent to true after boolean conversion
    * @assumptions:  bool convertor for T
    * */
    template <class T>
    bool any(const Matrix<T>& matrix);

    
    


    template <class T>
    void Matrix<T>::verifyIndex(const int row,const int col) const
    {
        if ((row < 0 || col < 0) || (row >= height() || col >= width())){
            throw AccessIllegalElement();
        }
    } 

    template <class T>
    void Matrix<T>::verifyDimensions(const Dimensions dimensions)
    {
        if(dimensions.getRow()<=0 || dimensions.getCol()<=0)
        {
            throw IllegalInitialization();
        }
    }

    

    template <class T>
    const char* Matrix<T>::AccessIllegalElement::what() const noexcept{
        return error_string.c_str();
    }
    
    template <class T>
    const char* Matrix<T>::IllegalInitialization::what() const noexcept{
        return error_string.c_str();
    }

    template <class T>
    const char* Matrix<T>::DimensionMismatch::what() const noexcept{
        return error_string.c_str();
    }

    /**Iterator Class: used to iterate over the elements of a matrix
    * */
    template <class T>
    class Matrix<T>::iterator {
        const Matrix<T>* matrix;
        int index;
        
        /**Iterator C'tor: Creates an iterator for the given matrix
        * */
        iterator(const Matrix<T>* matrix,int index);
        friend class Matrix<T>;
        public:
        /**dereference (operator*) returns the element pointed to by the iterator by reference
        * */
        T& operator*();

        /** prefix ++ operator (++it): advances the iterator one element forward
        * */
        iterator& operator++(); 
        
        /** postfix ++ operator (it++): advances the iterator one element forward after performing the rest of the code in the line
        * */
        iterator operator++(int); 
        
        /** == operator: returns true if the 2 given iterators point to the same element in the matrix, returns false otherwise 
        * */
        bool operator==(const iterator& other) const;

        /** == operator: returns true if the 2 given iterators point to different elements in the matrix, returns false otherwise 
        * */
        bool operator!=(const iterator& other) const;
    };

    template <class T>
    class Matrix<T>::const_iterator {
        const Matrix<T>* matrix;
        int index;
        /** Const Iterator C'tor: Creates an iterator for the given matrix
        * */
        const_iterator(const Matrix<T>* const matrix, int index);
        friend class Matrix<T>;
        public:
        /**dereference (operator*) returns the element pointed to by the const_iterator by reference
        * */
        const T& operator*() const;

        /** prefix ++ operator (++it): advances the const_iterator one element forward
        * */
        const_iterator& operator++(); 

        /** postfix ++ operator (it++): advances the iterator one element forward after performing the rest of the code in the line
        * */
        const_iterator operator++(int);

        /** == operator: returns true if the 2 given const_iterators point to the same element in the matrix, returns false otherwise 
        * */
        bool operator==(const const_iterator& other) const;

        /** == operator: returns true if the 2 given const_iterators point to different elements in the matrix, returns false otherwise 
        * */
        bool operator!=(const const_iterator& other) const;
    };


    template <class T>
    Matrix<T>::Matrix(const Dimensions dimensions, const T value) : dimensions(dimensions)
        {
            verifyDimensions(dimensions);
            int total_size = dimensions.getRow()*dimensions.getCol();
            data = new T[total_size]();
            for(int i = 0; i < total_size; i++){
                data[i] = value;
            }
        }


    template <class T>
    Matrix<T>::Matrix(const Matrix<T>& matrix) : dimensions(matrix.dimensions),data(new T[matrix.size()])
    {
        for(int i = 0; i < matrix.size(); i++){
            data[i] = matrix.data[i];
        }
    }   

    template <class T>
    Matrix<T> Matrix<T>::Diagonal(const int dimension,const T value)
    {
        Dimensions dimensions(dimension,dimension);
        verifyDimensions(dimensions);
        Matrix<T> matrix(dimensions);
        for (int i=0; i<dimension; i++){
            matrix(i,i) = value;
        }
        return matrix;
    }

    template <class T>
    Matrix<T> Matrix<T>::transpose() const{
        Dimensions result_dimensions(dimensions.getCol(), dimensions.getRow());
        Matrix<T> result(result_dimensions);
        int result_row = result.dimensions.getRow();
        int result_col = result.dimensions.getCol();
        for(int i=0; i < result_row; i++){
            for(int j=0; j < result_col; j++){
                result(i,j) = (*this)(j,i);
            }
        }
        return result;
    }    
        
    template <class T>
    Matrix<T>& Matrix<T>::operator+=(const T object){
        Matrix<T> object_matrix((*this).dimensions, object);
        *this = *this + object_matrix;
        return *this;
    }
    
    template <class T>
    Matrix<T> Matrix<T>::operator-() const
    {
        Matrix<T> result = *this;
        for(int i=0;i<(*this).height();i++){
            for (int j=0; j<(*this).width(); j++)
            {
                result(i,j) = -(*this)(i,j);
            }
        }
        return result;
    }

    template <class T>
    Matrix<T> operator+(const Matrix<T>& matrix_a, const Matrix<T>& matrix_b)
    {
        Dimensions dimensions_a(matrix_a.height(), matrix_a.width());
        Dimensions dimensions_b(matrix_b.height(), matrix_b.width());
        if(dimensions_a != dimensions_b)
        {
            throw typename Matrix<T>::DimensionMismatch(dimensions_a, dimensions_b);
        }
        Matrix<T> result = matrix_a;
        for(int i=0;i<matrix_a.height();i++){
            for (int j=0; j<matrix_a.width(); j++)
            {
                result(i,j) = matrix_a(i,j) + matrix_b(i,j);
            }
        }
        return result;
    }

    template <class T>
    Matrix<T> operator+(const T object, const Matrix<T>& matrix)
    {
        Dimensions dimensions(matrix.height(), matrix.width());
        Matrix<T> object_matrix(dimensions, object);
        return object_matrix+matrix; 
    }

    template <class T>
    Matrix<T> operator+(const Matrix<T>& matrix, const T object)
    {
        Matrix<T> result = matrix;    
        return result+=object;
    }

    template <class T>
    Matrix<T> operator-(const Matrix<T>& matrix_a, const Matrix<T>& matrix_b){
        Dimensions dimensions_a(matrix_a.height(), matrix_a.width());
        Dimensions dimensions_b(matrix_b.height(), matrix_b.width());
        if(dimensions_a != dimensions_b)
        {
            throw typename Matrix<T>::DimensionMismatch(dimensions_a, dimensions_b);
        }
        Matrix<T> result = matrix_a;
        for(int i=0;i<matrix_a.height();i++){
            for (int j=0; j<matrix_a.width(); j++)
            {
                result(i,j) = matrix_a(i,j) - matrix_b(i,j);
            }
        }
        return result;
    }

    
    template <class T>
    Matrix<T>& Matrix<T>::operator=(const Matrix<T>& matrix)
    {
        if(this == &matrix){
            return *this;
        }
        T* new_data = new T[matrix.size()];
        try {
            for (int i = 0; i < matrix.size(); ++i) {
                new_data[i] = matrix.data[i];
            }
        } catch (...) {
            delete[] new_data;
            throw;
        }
        delete[] data;
        data=new_data;
        dimensions=matrix.dimensions;
        return *this;
    }
    
    template <class T>
    Matrix<bool> operator<(const Matrix<T>& matrix,const T object){
        Dimensions dimensions(matrix.height(), matrix.width());
        Matrix<bool> result(dimensions);
        for(int i=0;i<result.height();i++){
            for (int j=0; j<result.width(); j++)
            {
                if (matrix(i,j) < object){
                    result(i,j) = true;
                }
            }
        }
        return result;
    }

    template <class T>
    Matrix<bool> operator==(const Matrix<T>& matrix,const T object){
        Dimensions dimensions(matrix.height(), matrix.width());
        Matrix<bool> result(dimensions);
        for(int i=0;i<result.height();i++){
            for (int j=0; j<result.width(); j++)
            {
                if (matrix(i,j) == object){
                    result(i,j) = true;
                }
            }
        }
        return result;
    }
    
    template <class T>
    Matrix<bool> operator<=(const Matrix<T>& matrix, const T object){
        Dimensions dimensions(matrix.height(), matrix.width());
        Matrix<bool> result(dimensions);
        return result+(matrix<object)+(matrix==object);
    }

    template <class T>
    Matrix<bool> operator>=(const Matrix<T>& matrix,const T object){
        Dimensions dimensions(matrix.height(), matrix.width());
        Matrix<bool> result(dimensions);
        return result+(matrix>object)+(matrix==object);
    }

    template <class T>
    Matrix<bool> operator>(const Matrix<T>& matrix,const T object){
        Dimensions dimensions(matrix.height(), matrix.width());
        Matrix<bool> result(dimensions,true);
        return result-(matrix<=object);
    }

    template <class T>
    Matrix<bool> operator!=(const Matrix<T>& matrix,const T object){
        Dimensions dimensions(matrix.height(), matrix.width());
        Matrix<bool> result(dimensions,true);
        return result-(matrix==object);
    }    

    template <class T>
    T& Matrix<T>::operator()(const int row, const int col)
    {
        verifyIndex(row, col);
        return data[width()*row + col];
    }

    template <class T>
    const T& Matrix<T>::operator()(const int row, const int col) const
    {
        verifyIndex(row, col);
        return data[width()*row + col];
    }

    template <class T>
    int Matrix<T>::height() const
    {
        return dimensions.getRow();
    }

    template <class T>
    int Matrix<T>::width() const
    {
        return dimensions.getCol();
    }

    template <class T>
    int Matrix<T>::size() const
    {
        return dimensions.getRow()*dimensions.getCol();
    }

    template <class T>
    std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix)
    {
        typename Matrix<T>::const_iterator begin = matrix.begin();
        typename Matrix<T>::const_iterator end = matrix.end();
        printMatrix(os,begin,end, matrix.width());
        return os;
    }

    template <class T>
    bool all(const Matrix<T>& matrix)
    {
        int height=matrix.height();
        int width=matrix.width();
        for(int i=0;i<height;i++){
            for (int j=0; j<width; j++){
                if (!(bool)matrix(i,j)){
                    return false;
                }
            }
        }
        return true;
    }

    template <class T>
    bool any(const Matrix<T>& matrix)
    {
        int height=matrix.height();
        int width=matrix.width();
        for(int i=0;i<height;i++){
            for (int j=0; j<width; j++){
                if ((bool)matrix(i,j)){
                    return true;
                }
            }
        }
        return false;
    }        
    
    template <class T>
    template<class action>
    Matrix<T> Matrix<T>::apply(action apply_action) const
    {
        Matrix<T> new_matrix = *this;
        int height=(*this).height();
        int width=(*this).width();
        for(int i=0;i<height;i++){
            for (int j=0; j<width; j++){
                new_matrix(i,j)=apply_action(new_matrix(i,j));
            }
        }
        return new_matrix;
    }

    template <class T>
    Matrix<T>::~Matrix()
    {
        delete[] data;
    }

    template <class T>
    typename Matrix<T>::iterator Matrix<T>::begin(){
        return iterator(this, 0);
    }
    
    template <class T>
    typename Matrix<T>::iterator Matrix<T>::end(){
        return iterator(this,size());
    }

    template <class T>
    Matrix<T>::iterator::iterator(const Matrix<T>* matrix,int index): matrix(matrix),index(index)
    { }

    template <class T>
    T& Matrix<T>::iterator::operator*(){
        matrix->verifyIndex(index/matrix->width(),index%matrix->width());
        return matrix->data[index];
    }

    template <class T>
    typename Matrix<T>::iterator& Matrix<T>::iterator::operator++() // prefix (++it)
    {
        ++index;
        return *this;
    }

    template <class T>
    typename Matrix<T>::iterator Matrix<T>::iterator::operator++(int)
    {
        iterator result = *this;
        ++*this;
        return result;
    }

    template <class T>
    bool Matrix<T>::iterator::operator==(const iterator& other) const
    {
        if(other.matrix != matrix){
            return false;
        }
        return index == other.index;
    }

    template <class T>
    bool Matrix<T>::iterator::operator!=(const iterator& other) const
    {
        return !(*this==other);
    }

    template <class T>
    typename Matrix<T>::const_iterator Matrix<T>::begin() const{
        return const_iterator(this, 0);
    }
    
    template <class T>
    typename Matrix<T>::const_iterator Matrix<T>::end() const{
        return const_iterator(this,size());
    }

    template <class T>
    Matrix<T>::const_iterator::const_iterator(const Matrix<T>* matrix,int index): matrix(matrix),index(index)
    { }

    template <class T>
    const T& Matrix<T>::const_iterator::operator*() const{
        matrix->verifyIndex(index/matrix->width(),index%matrix->width());
        return matrix->data[index];
    }

    template <class T>
    typename Matrix<T>::const_iterator& Matrix<T>::const_iterator::operator++() // prefix (++it)
    {
        ++index;
        return *this;
    }

    template <class T>
    typename Matrix<T>::const_iterator Matrix<T>::const_iterator::operator++(int)
    {
        const_iterator result = *this;
        ++*this;
        return result;
    }

    template <class T>
    bool Matrix<T>::const_iterator::operator==(const const_iterator& other) const
    {
        if(other.matrix != matrix){
            return false;
        }
        return index == other.index;
    }

    template <class T>
    bool Matrix<T>::const_iterator::operator!=(const const_iterator& other) const
    {
        return !(*this==other);
    }
}



#endif //Matrix_H

