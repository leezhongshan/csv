#include "csv2.h"
#include <iostream>
#include <functional>

typedef std::function< void(bool bSuccess, const std::vector<std::string>& cols, int nLine, const std::string& strError) >  CsvRowFn_t;


bool LoadCsv(const std::string& strFile, const std::vector<std::string>& header, int man, CsvRowFn_t onCsvRowFn)
{	

	io::CSVReader<io::trim_chars<' ','\t'>, io::double_quote_escape<',','"'>>  reader(strFile.c_str());
	
	try
	{
		reader.read_header(io::ignore_extra_column , header);
		onCsvRowFn(true, header, reader.get_file_line(), "");	
	}	 
	catch (io::error::missing_column_in_header& e)
	{
 		onCsvRowFn(false, header, reader.get_file_line(), e.what());

	}
	catch (io::error::base& e)
	{
		onCsvRowFn(false, header, reader.get_file_line(), e.what());

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
		
			onCsvRowFn(true,  cols, reader.get_file_line(), "");

		}
		catch (io::error::escaped_string_not_closed& e)  // 语法错误
		{
			onCsvRowFn(false, cols, reader.get_file_line(), e.what());


		}		 
		catch (io::error::base& e)
		{ 
			onCsvRowFn(false, cols, reader.get_file_line(), e.what());
		}	 

	}
	


	 

	return true;
}
 
 

int main()
{
    std::vector<std::string> header = { "col1", "col2","col3"};
    
    LoadCsv("a.csv", header,[&](bool bSuccess, const std::vector< std::string>& cols, int nLine, const std::string& strError) 
    {
          if(nLine == 1)  // header
          {              
              
              return ;
          }
          
          for( auto strCol : cols)
              std::cout<< strCol;
          std::cout<<endl;
          
    });
}


