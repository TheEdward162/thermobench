#include "csvRow.h"


/* CsvColumn implementation */

CsvColumn::CsvColumn(std::string header, unsigned int order)
{
    this->header = header;
    this->order = order;
}

std::string CsvColumn::getHeader() const
{
    return header;
}

unsigned int CsvColumn::getOrder() const
{
    return order;
}

/* CsvColumns implementation */

CsvColumns::~CsvColumns()
{
    for (auto p : columns)
        delete p;
    columns.clear();
};

CsvColumn *CsvColumns::add(std::string name)
{
    CsvColumn *newColumn = new CsvColumn(name, columns.size());
    if (newColumn) {
        columns.push_back(newColumn);
        return columns.back();
    }
    return NULL;
}

void CsvColumns::setHeader(CsvRow &row)
{
    for (CsvColumn *column : columns) {
        row.set(column, column->getHeader());
    }
}

/* CsvRow implementation */
void CsvRow::set(CsvColumn *column, double data)
{
    if (column) {
        char buf[100];
        sprintf(buf, "%g", data);
        set(column, buf);
    }
};

void CsvRow::set(CsvColumn *column, std::string data)
{
    if (column) {
        const unsigned int order = column->getOrder();
        data = csvEscape(data);
        if (order < row.size()) {
            row[order] = data;
        } else {
            while (row.size() < order) {
                row.push_back("");
            }
            row.push_back(data);
        }
    }
};

std::string CsvRow::getValue(CsvColumn *column) const
{
    if (column) {
        const unsigned int order = column->getOrder();
        return (order < row.size()) ? row[column->getOrder()] : "";
    }
    return NULL;
}

std::string CsvRow::toString() const
{
    std::string line;
    for (const std::string &str : row) {
        line.append(str);
        line.push_back(',');
    }
    line.pop_back(); // remove last ','
    line.push_back('\n');
    return line;
}

void CsvRow::write(FILE *fp)
{
    if (fp)
        fprintf(fp, "%s", (toString()).c_str());
}

void CsvRow::clear()
{
    row.clear();
}

bool CsvRow::empty() const
{
    return row.empty();
}

std::string csvEscape(std::string unsafe)
{
    // Each of the embedded double-quote characters
    // must be represented by a pair of double-quote characters
    int first = 0;
    while ((first = unsafe.find_first_of('"', first)) >= 0) {
        unsafe.insert(first, "\"");
        first += 2; // after insert index of founded character is incremented, therefore +2
    }
    // Fields with embedded commas or line breaks characters must be quoted
    int comma, whitespace;
    if ((comma = unsafe.find_first_of(',')) >= 0 || (whitespace = unsafe.find_first_of(' ')) >= 0) {
        unsafe.insert(0, "\"");
        unsafe.push_back('"');
    }
    return unsafe;
}
