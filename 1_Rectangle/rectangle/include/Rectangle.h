#ifndef HFE81C6DD_FADF_4211_A26A_BFE859638926
#define HFE81C6DD_FADF_4211_A26A_BFE859638926

struct Rectangle
{
    Rectangle(double width, double height);
    double area() const;
    double perimeter() const;
    inline double getWidth() const
    {
        return m_width;
    }
    inline double getHeight() const
    {
        return m_height;
    }
private:
    bool isVaild() const ;
 private:
    double m_width;
    double m_height;
};

#endif /* HFE81C6DD_FADF_4211_A26A_BFE859638926 */
