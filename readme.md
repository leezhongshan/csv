
usage:

io::CSVReader<io::trim_chars<' ', '\t'>, io::double_quote_escape<',', '"'>>  reader(strFile.c_str());

try
{
    reader.read_header(io::ignore_extra_column, header);

}
catch (io::error::missing_column_in_header& e)
{


}
catch (io::error::base& e)
{


}

std::vector<std::string> cols;
cols.resize(header.size());

while (true)
{
    try
    {
        if (!reader.read_row(cols))
        {
            break;
        }
    }
    catch (io::error::escaped_string_not_closed& e)
    {  }
    catch (io::error::base& e)
    { }
    
  }	
