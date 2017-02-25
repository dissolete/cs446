#include <pthread.h>
#include "Utilities.hpp"
#include "Parser.hpp"
#include "Substring.hpp"
#include "Time.hpp"


int get_total_instruction_time(const jgs::ConfigStruct & configStruct, const jgs::Instruction & instruction )
{
  if(instruction.instructionDesc == "keyboard")
    return instruction.instructionTime * configStruct.keyboardTime;
  if(instruction.instructionDesc == "monitor")
    return instruction.instructionTime * configStruct.monitorTime;
  if(instruction.instructionDesc == "speaker")
    return instruction.instructionTime * configStruct.speakerTime;
  if(instruction.instructionDesc == "harddrive")
    return instruction.instructionTime * configStruct.hddTime;
  if(instruction.instructionDesc == "run")
    return instruction.instructionTime * configStruct.processorTime;
  if(instruction.instructionDesc == "allocate")
    return instruction.instructionTime * configStruct.memoryTime;
  if(instruction.instructionDesc == "block")
    return instruction.instructionTime * configStruct.memoryTime;
  if(instruction.instructionDesc == "printer")
    return instruction.instructionTime * configStruct.printerTime;
}

void log(std::ofstream & ofs, jgs::ConfigStruct::LogStyle logStyle, std::string outputString)
{
  if(logStyle == jgs::ConfigStruct::LogStyle::LogToBoth)
  {
    std::cout << outputString << std::endl;
    ofs << outputString << '\n';
  }
  else if(logStyle == jgs::ConfigStruct::LogStyle::LogToFile)
  {
    ofs << outputString << '\n';
  }
  else
  {
    std::cout << outputString << std::endl;
  }
}

void output_config_metrics(const std::vector<jgs::Instruction> &instructions, const jgs::ConfigStruct &configStruct)
{
  std::ofstream ofs;
  jgs::ConfigStruct::LogStyle logStyle = configStruct.logStyle;
  ofs.open(configStruct.logPath);
  if(!ofs.good())
  {
    std::cout << "The file " << configStruct.logPath << " could not be opened. Check if the directory exists." << std::endl;
    logStyle = jgs::ConfigStruct::LogStyle::LogToMonitor;
  }

  log(ofs, logStyle, "Configuration File Data");
  std::string output;
  // Output all of the config stuff
  if(configStruct.processorTime > -1)
  {
    output = "Processor = " + std::to_string(configStruct.processorTime) + std::string(" ms/cycle");
    log(ofs, logStyle, output);
  }
  if(configStruct.monitorTime > -1)
  {
    std::string output = "Monitor = " + std::to_string(configStruct.monitorTime) + std::string(" ms/cycle");
    log(ofs, logStyle, output);
  }
  if(configStruct.hddTime > -1)
  {
    std::string output = "Hard Drive = " + std::to_string(configStruct.hddTime) + std::string(" ms/cycle");
    log(ofs, logStyle, output);
  }
  if(configStruct.printerTime > -1)
  {
    std::string output = "Printer = " + std::to_string(configStruct.printerTime) + std::string(" ms/cycle");
    log(ofs, logStyle, output);
  }
  if(configStruct.speakerTime > -1)
  {
    std::string output = "Speaker = " + std::to_string(configStruct.speakerTime) + std::string(" ms/cycle");
    log(ofs, logStyle, output);
  }
  if(configStruct.mouseTime > -1)
  {
    std::string output = "Mouse = " + std::to_string(configStruct.mouseTime) + std::string(" ms/cycle");
    log(ofs, logStyle, output);
  }
  if(configStruct.keyboardTime > -1)
  {
    std::string output = "Keyboard = " + std::to_string(configStruct.keyboardTime) + std::string(" ms/cycle");
    log(ofs, logStyle, output);
  }
  if(configStruct.memoryTime > -1)
  {
    std::string output = "Memory = " + std::to_string(configStruct.processorTime) + std::string(" ms/cycle");
    log(ofs, logStyle, output);
  }

  output = "Logged to: ";
  if(configStruct.logPath != ""){
    switch(configStruct.logStyle)
    {
      case jgs::ConfigStruct::LogStyle::LogToBoth:
        output += "monitor and " + jgs::substr_from_delim(configStruct.logPath, '/');
        break;
      case jgs::ConfigStruct::LogStyle::LogToMonitor:
        output += "monitor";
        break;
      case jgs::ConfigStruct::LogStyle::LogToFile:
        output += jgs::substr_from_delim(configStruct.logPath, '/');
        break;
    }
    log(ofs, logStyle, output);
  }

  log(ofs, logStyle, "\nMeta-Data Metrics");

  for(const jgs::Instruction & instruction : instructions)
  {
    if(instruction.instructionDesc == "start" or instruction.instructionDesc == "end")
      continue;
    output = instruction.instructionCode;
    output += "(" + instruction.instructionDesc + ")";
    output += std::to_string(instruction.instructionTime);
    output += " - " + std::to_string(get_total_instruction_time(configStruct, instruction));
    output += " ms";
    log(ofs, logStyle, output);
  }

  ofs.close();
}

std::string process_instruction(const jgs::ConfigStruct &configStruct, const jgs::Instruction &theInstruction)
{
	// init output with timer
	std::string output = std::to_string(Time::elapsed());

	if(theInstruction.instructionCode == 'S')
	{
    if(theInstruction.instructionDesc == "start"){
      output += " - OS: preparing process 1";
      Time::wait(get_total_instruction_time(configStruct, theInstruction));

    }
    else if(theInstruction.instructionDesc == "end"){
      output += " - OS: removing process 1";
      Time::wait(get_total_instruction_time(configStruct, theInstruction));

    }
  }
  else if(theInstruction.instructionCode == 'A')
  {
    if(theInstruction.instructionDesc == "start"){
      output += " - OS: starting process 1";
      Time::wait(get_total_instruction_time(configStruct, theInstruction));

    }
  }
  else if(theInstruction.instructionCode == 'P')
  {
    output += " - Process 1: start process action";
    Time::wait(get_total_instruction_time(configStruct, theInstruction));
    output += std::to_string(Time::elapsed()) + " - Process 1: end process action";
  }
}

int main(int argc, char ** argv)
{
  using namespace jgs;

  // Abort if user did not supply a config file!
  FATAL_ERROR_CHECK(argc <= 1, "A configuration file must be supplied for proper simulation!");

  Parser parser;


  if(not parser.parse(argv[1]))
  {
	  std::cout << "+-----------------------------------------------------------------------------+" << std::endl;
	  std::cout << "One or more errors occured while attempting to parse the configuration files!\n"
			    << "Error(s): ";
	  std::cout << parser.get_error() << std::endl;
	  std::cout << "+-----------------------------------------------------------------------------+" << std::endl;
	  return -1;
  }

  //output_config_metrics(parser.m_instructions, parser.m_configStruct);

  std::ofstream ofs;
  jgs::ConfigStruct::LogStyle logStyle = parser.m_configStruct.logStyle;
  ofs.open(parser.m_configStruct.logPath);
  if(!ofs.good())
  {
    std::cout << "The file " << parser.m_configStruct.logPath << " could not be opened. Check if the directory exists." << std::endl;
    logStyle = jgs::ConfigStruct::LogStyle::LogToMonitor;
  }

  // Reset timer
  Time::reset();

  log(ofs, logStyle, std::to_string(Time::elapsed()) + " - Simulator Program Starting");

  // Iterate through instructions, creating threads
  for(auto instruction : parser.m_instructions)
  {
		log(ofs, logStyle, process_instruction(parser.m_configStruct ,instruction));

  }

  ofs.close();

  return 0;

}
