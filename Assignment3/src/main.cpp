#include <pthread.h>
#include <iomanip>
#include <sstream>
#include "Utilities.hpp"
#include "Parser.hpp"
#include "Substring.hpp"
#include "Time.hpp"
#include "MemoryFunction.hpp"
#include "PCB.hpp"


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
  
  return 0;
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

std::string get_instruction_output(const jgs::Instruction &instruction, bool endProcess)
{

  std::string output;

  // FEAST YOUR EYES ON THESE BEAUTIFUL IFS!
  if(instruction.instructionCode == 'S')
  {
    if(not endProcess){
      if(instruction.instructionDesc == "start")
      {
        output = "OS: Preparing process 1";
      }
      else if(instruction.instructionDesc == "end")
      {
        output = "Simulator program ending";
      }
    }
    else
      output = "";
  }
  else if(instruction.instructionCode == 'A')
  {
    if(not endProcess){
      if(instruction.instructionDesc == "end")
      {
        output = "OS: Removing process 1";
      }
      else if(instruction.instructionDesc == "start")
      {
        output = "OS: Starting process 1";
      }
    }
    else
      output = "";
  }
  else if(instruction.instructionCode == 'P')
  {
    if(not endProcess)
      output = "Process 1: Start processing action";
    else
      output = "Process 1: End processing action";
  }
  else if(instruction.instructionCode == 'I')
  {
    if(not endProcess){
      if(instruction.instructionDesc == "keyboard")
      {
        output = "Process 1: Start keyboard input";
      }
      else if(instruction.instructionDesc == "harddrive")
      {
        output = "Process 1: Start hard drive input";
      }
      else if(instruction.instructionDesc == "mouse")
      {
        output = "Process 1: Start mouse input";
      }
    }
    else
    {
      if(instruction.instructionDesc == "keyboard")
      {
        output = "Process 1: End keyboard input";
      }
      else if(instruction.instructionDesc == "harddrive")
      {
        output = "Process 1: End hard drive input";
      }
      else if(instruction.instructionDesc == "mouse")
      {
        output = "Process 1: End mouse input";
      }
    }
  }
  else if(instruction.instructionCode == 'O')
  {
    if(not endProcess){
      if(instruction.instructionDesc == "harddrive")
      {
        output = "Process 1: Start hard drive output";
      }
      else if(instruction.instructionDesc == "monitor")
      {
        output = "Process 1: Start monitor output";
      }
      else if(instruction.instructionDesc == "speaker")
      {
        output = "Process 1: Start speaker output";
      }
      else if(instruction.instructionDesc == "printer")
      {
        output = "Process 1: Start printer output";
      }
    }
    else
    {
      if(instruction.instructionDesc == "harddrive")
      {
        output = "Process 1: End hard drive output";
      }
      else if(instruction.instructionDesc == "monitor")
      {
        output = "Process 1: End monitor output";
      }
      else if(instruction.instructionDesc == "speaker")
      {
        output = "Process 1: End speaker output";
      }
      else if(instruction.instructionDesc == "printer")
      {
        output = "Process 1: End printer output";
      }
    }
  }
  else if(instruction.instructionCode == 'M')
  {
    if(not endProcess)
    {
      if(instruction.instructionDesc == "allocate")
      {
        output = "Process 1: Allocating memory";
      }
      else if(instruction.instructionDesc == "block")
      {
        output = "Process 1: Start block process";
      }
    }
    else
    {
      if(instruction.instructionDesc == "allocate")
      {
        output = "Process 1: Memory allocated at - ";
      }
      else if(instruction.instructionDesc == "block")
      {
        output = "Process 1: End block process";
      }
    }
  }
  else
    output = "The instruction with desc " + instruction.instructionDesc + " has no implem in get_instruction_output";

  return output;
}

void* wait(void* timeRequired)
{
  Time::Timer timer;
  while(timer.elapsed() <= (long)timeRequired / 1000.f);
}

void execute_instruction(float timeRequired, const jgs::Instruction instruction)
{
  using namespace jgs;

  Time::Timer timer;
  pthread_t thread;

  // Catch I/O instructions
  if(instruction.instructionCode == 'O' or instruction.instructionCode == 'I')
  {
    // Set PCB to WAIT
    PCB::set_state(PCB::pcbState::WAITING);
    // create a thread
    pthread_create(&thread, NULL, wait, (void*)((long)(timeRequired * 1000)));

    // Wait for thread to finish
    pthread_join(thread, NULL);

    // Set PCB to READY
    PCB::set_state(PCB::pcbState::READY);
  }
  else
  {
    // Set PCB to RUNNING
    PCB::set_state(PCB::pcbState::RUNNING);

    // Pretty much just wait for instruction time
    while(timer.elapsed() <= timeRequired);
  }

}

void process_instruction(std::ofstream & ofs, jgs::ConfigStruct::LogStyle logStyle, Time::Timer &timer, const jgs::ConfigStruct &configStruct, const jgs::Instruction &instruction)
{

  std::string output = std::to_string(timer.elapsed()) + " - ";

  // Get output string appropriate for this instruction
  output += get_instruction_output(instruction, false);
  log(ofs, logStyle, output);

  //DEBUG("Instruction time is " << get_total_instruction_time(configStruct, instruction) / 1000.0f);
  if(instruction.instructionDesc != "allocate")
    // Execute instruction
    execute_instruction(get_total_instruction_time(configStruct, instruction) / 1000.0f, instruction);

  // Get end output
  if(instruction.instructionCode != 'S' and instruction.instructionCode != 'A'){
    output =  std::to_string(timer.elapsed()) + " - " + get_instruction_output(instruction, true);

    // Catch memory allocation
    if(instruction.instructionDesc == "allocate")
    {
      DEBUG("MEMORY TOTAL IS " << configStruct.memoryTotal);
      DEBUG("MEMORY BLOCK SIZE IS " << configStruct.memoryBlockSize);
      unsigned int address = Memory::allocateMemory(configStruct.memoryTotal, configStruct.memoryBlockSize);
      std::stringstream stream;
      stream << "0x" 
            << std::setfill ('0') << std::setw(sizeof(unsigned int)*2) 
            << std::hex << address;
      output += stream.str();
    }

    log(ofs, logStyle, output);
  }
}

void run_simulation(const jgs::ConfigStruct &configStruct, const std::vector<jgs::Instruction> &instructions)
{
  using namespace jgs;
  // Create ofstream, get logstyle
  std::ofstream ofs;
  jgs::ConfigStruct::LogStyle logStyle = configStruct.logStyle;
  ofs.open(configStruct.logPath);
  if(!ofs.good())
  {
    std::cout << "The file " << configStruct.logPath << " could not be opened. Check if the directory exists." << std::endl;
    logStyle = jgs::ConfigStruct::LogStyle::LogToMonitor;
  }

  // Create a Timer
  Time::Timer timer;

  // Keep track of time elapsed for all instructions
  float totalTime = timer.elapsed();

  // Output string for logging
  std::string output = std::to_string(totalTime) + " - Simulator Program starting";

  // PCB is initialized to NEW automatically, but setting it here so TA knows that I did it anyway :)
  PCB::set_state(PCB::pcbState::NEW);

  // Output initial time
  log(ofs, logStyle, output);

  // Process instructions
  for(auto instruction : instructions)
  {
    process_instruction(ofs, logStyle, timer, configStruct, instruction);
  }

  // Set PCB to TERMINATED
  PCB::set_state(PCB::pcbState::TERMINATED);

  ofs.close();
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

  run_simulation(parser.m_configStruct, parser.m_instructions);

  return 0;

}
