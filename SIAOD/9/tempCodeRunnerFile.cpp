
struct specialization
{
    int code;
    std::string university_name;
    int start_year;
};

void fill_records(specialization* specializations, int size)
{
    for (int i = 0; i < size; i++)
    {
        specializations[i].code = i + 1;
        specializations[i].university_name = "uni №" + std::to_string(i + 1);
        specializations[i].start_year = 2000 + i;
    }
}