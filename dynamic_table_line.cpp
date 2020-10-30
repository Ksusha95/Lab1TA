std::string dynamic_table_line(int numSize) {

    int sizeLine = 9 + (numSize * 4);
    std::string lineTable(std::string(sizeLine, '-'));

    return lineTable;

}
