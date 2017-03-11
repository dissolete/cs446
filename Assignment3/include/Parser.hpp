#ifndef __PARSER_HPP_INCLUDED
#define __PARSER_HPP_INCLUDED

#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cstdlib>
#include "Substring.hpp"
#include "Utilities.hpp"

namespace jgs
{

  struct ConfigStruct
  {
    enum LogStyle
    {
      LogToBoth, LogToMonitor, LogToFile
    };

    int version = -1;
    int processorTime = -1;
    int monitorTime = -1;
    int hddTime = -1;
    int printerTime = -1;
    int keyboardTime = -1;
    int memoryTime = -1;
    int mouseTime = -1;
    int speakerTime = -1;
    int hddQuantity = -1;
    int memoryTotal = -1;
    int printerQuantity = -1;
    int memoryBlockSize = -1;

    std::string metafile = "";
    std::string logPath = "";
    LogStyle logStyle = LogStyle::LogToMonitor;
  };

  struct Instruction
  {
    std::string instructionDesc = "";
    char instructionCode = '\0';
    int instructionTime = -1;
  };

  class Parser
  {
    public:
      std::vector<Instruction> m_instructions;
      ConfigStruct m_configStruct;
	  enum State
	  {
		  BeginState, EndState, FatalState, FilePathState,
      ProcessorState, MonitorState, HDDState, PrinterState,
      KeyboardState, MemoryState, MouseState, SpeakerState,
      MetaPathState, LogPathState, LogStyleState, SkipState,
      SystemMemoryState
	  };

    class Word
    {
    public:

      Word(State theState, std::string theName) : state(theState), name(theName){}

      State state;
      std::string name;
    };

    /**
    * Default constructor.
    */
    Parser();

    /**
    * Parses the config file. Throws an exception if there is an error in
    * the config file
    */
    bool parse(std::string configFile);

    /**
     * If an error occured, this will return the error message.
     * If no error, an empty string is returned
     */
    std::string get_error() const;

    protected:

     bool parse_config();
     bool parse_meta();

     Parser::State check_valid_word(std::string word);
     bool check_valid_syntax(std::string instructionString, Instruction & instructionStruct);
     std::string extract_instruction();

     bool check_valid_code(char instructionCode);
     bool check_valid_desc(std::string desc);

     bool perform_BeginState();
     bool perform_EndState();
     bool perform_FatalState();
     bool perform_FilePathState();
     bool perform_ProcessorState();
     bool perform_MonitorState();
     bool perform_HDDState();
     bool perform_PrinterState();
     bool perform_KeyboardState();
     bool perform_MemoryState();
     bool perform_MouseState();
     bool perform_SpeakerState();
     bool perform_MetaPathState();
     bool perform_LogStyleState();
     bool perform_LogPathState();
     
     // Assignment 3 states
     bool perform_MemoryBlockState();
     bool perform_HDDQuantityState();
     bool perform_PrinterQuantityState();
     bool perform_SystemMemoryState();
     
     bool perform_SkipState(std::string skippedWord);


    private:

      State m_currentState;

      std::fstream m_inf;

      std::string m_configFile, m_metaFile, m_errorString;

      std::vector<Word> m_validWords;
      std::vector<char> m_validInstructionCodes;
      std::vector<std::string> m_validInstructionDescs;
  };

}

#endif
