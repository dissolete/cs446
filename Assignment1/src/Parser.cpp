#include "Parser.hpp"

namespace jgs
{
  Parser::Parser()
  	  : m_currentState(Parser::State::BeginState)
  	  , m_errorString("")
  {
    m_validWords = {
      Word(State::BeginState, "Start"),
      Word(State::FilePathState, "File"),
      Word(State::ProcessorState, "Processor"),
      Word(State::MonitorState, "Monitor"),
      Word(State::HDDState, "Hard"),
      Word(State::PrinterState, "Printer"),
      Word(State::KeyboardState, "Keyboard"),
      Word(State::MemoryState, "Memory"),
      Word(State::MouseState, "Mouse"),
      Word(State::SpeakerState, "Speaker"),
      Word(State::LogStyleState, "Log:"),
      Word(State::LogPathState, "Log"),
      Word(State::EndState, "End")
    };
  }

  std::string Parser::get_error() const
  {
	  return m_errorString;
  }

  bool Parser::parse(std::string configFile)
  {

  	// Check file extension and return false if there is a mismatch
  	std::string extension = substr_from_delim(configFile, '.');
  	if( extension != "conf")
  	{
  		m_errorString += "* The extension " + extension + " is not supported by the parser! "
  					  + "The extension must be .conf";
  		return false;
  	}

  	m_configFile = configFile;

  	bool success = parse_config();

    if(success)
    {
      std::cout << "The config file has been parsed correctly! :)\n";
      std::cout << "The contents of the config struct are:\n";
      std::cout << "Processor time: " << m_configStruct.processorTime << std::endl;
      std::cout << "Monitor time: " << m_configStruct.monitorTime << std::endl;
      std::cout << "HDD Time: " << m_configStruct.hddTime <<  std::endl;
      std::cout << "Printer Time: " << m_configStruct.printerTime <<  std::endl;
      std::cout << "Keyboard Time: " << m_configStruct.keyboardTime <<  std::endl;
      std::cout << "Memory Time: " << m_configStruct.memoryTime <<  std::endl;
      std::cout << "Mouse Time: " << m_configStruct.mouseTime <<  std::endl;
      std::cout << "Speaker Time: " << m_configStruct.speakerTime <<  std::endl;
      std::cout << "Metafile: " << m_configStruct.metafile <<  std::endl;
      std::cout << "LogPath: " << m_configStruct.logPath <<  std::endl;
      std::cout << "LogStle: " << m_configStruct.logStyle <<  std::endl;
    }

    success = parse_meta();
  	return success;

  }

  bool Parser::parse_config()
  {

	  // Open the config file and throw exception if it could not be opened
	  m_inf.open(m_configFile.c_str());
	  if(not m_inf.is_open())
	  {
		  m_errorString += "* The configuration file " + m_configFile
				        + " supplied cannot be opened. Does it exist?";

		  m_currentState = State::FatalState;
	  }


	  // Grab first word
	  std::string inputString;
	  m_inf >> inputString;

    bool stateSuccess;
	  while(m_inf.good() and m_currentState != State::FatalState and m_currentState != State::EndState)
	  {
		  // Get next state
		  m_currentState = check_valid_word(inputString);

      switch(m_currentState)
      {
        case State::BeginState: 
              stateSuccess = perform_BeginState();
              break;
        case State::EndState: 
              stateSuccess = perform_EndState();
              m_currentState = State::EndState;
              break;
        case State::FatalState: 
              stateSuccess = perform_FatalState();
              break;
        case State::FilePathState: 
              stateSuccess = perform_FilePathState();
              break;
        case State::ProcessorState: 
              stateSuccess = perform_ProcessorState();
              break; 
        case State::MonitorState: 
              stateSuccess = perform_MonitorState();
              break; 
        case State::HDDState: 
              stateSuccess = perform_HDDState();
              break;
        case State::PrinterState: 
              stateSuccess = perform_PrinterState();
              break;
        case State::KeyboardState: 
              stateSuccess = perform_KeyboardState();
              break;
        case State::MemoryState: 
              stateSuccess = perform_MemoryState();
              break;
        case State::MouseState: 
              stateSuccess = perform_MouseState();
              break; 
        case State::SpeakerState: 
              stateSuccess = perform_SpeakerState();
              break;
        case State::MetaPathState: 
              stateSuccess = perform_MetaPathState();
              break;
        case State::LogPathState: 
              stateSuccess = perform_LogPathState();
              break;
        case State::LogStyleState: 
              stateSuccess = perform_LogStyleState();
              break; 
        case State::SkipState: 
              stateSuccess = perform_SkipState(inputString);
              break;

      }

      if(stateSuccess)
		    // Get next word
		    m_inf >> inputString;
      else
        m_currentState = State::FatalState;

	  }

	  m_inf.close();

	  return m_currentState == State::FatalState ? false : true;
  }

  Parser::State Parser::check_valid_word(std::string theWord)
  {
    State state;

    // Iterate through valid words
    for(auto word : m_validWords)
    {
      // If we found a match
      if(word.name == theWord)
      {
        // return the state attached to the word
        state = word.state;
        return state;
      }
    }

    return State::SkipState;
  }

  bool Parser::perform_BeginState()
  {
    DEBUG("");
    // Skip the next three words
    std::string dummy;
    m_inf >> dummy;
    m_inf >> dummy;
    m_inf >> dummy;

    return true;
  }

  bool Parser::perform_EndState()
  {
     DEBUG("");
  }

  bool Parser::perform_FatalState()
  {
     DEBUG("");
  }

  bool Parser::perform_FilePathState()
  {

    DEBUG("");

    std::string input;
    // First word should be path:
    m_inf >> input;

    // Second word should be the filepath
    m_inf >> input;

    // Check the extension of the filepath
    std::string extension = substr_from_delim(input, '.'); 
    if(extension != "mdf")
    {
      m_errorString += "\n* The extension " + extension + " is not supported for the meta "
                    +  "data file. The extension must be mdf. The filepath supplied is "
                    + input;
      return false;
    }

    m_configStruct.metafile = input;

    return true;
  }

  bool Parser::perform_ProcessorState()
  {

    std::string input;
    // Skip next three words
    m_inf >> input;
    m_inf >> input;
    m_inf >> input;

    // Last is an int
    m_inf >> m_configStruct.processorTime;
    DEBUG("The int is " << m_configStruct.processorTime);
    return true;
  }

  bool Parser::perform_MonitorState()
  {
     std::string input;
    // Skip next three words
    m_inf >> input;
    m_inf >> input;
    m_inf >> input;

    // Last is an int
    m_inf >> m_configStruct.monitorTime;
    DEBUG("The int is " << m_configStruct.monitorTime);
    return true;
  }

  bool Parser::perform_HDDState()
  {
    std::string input;
    // Skip next four words
    m_inf >> input;
    m_inf >> input;
    m_inf >> input;
    m_inf >> input;

    // Last is an int
    m_inf >> m_configStruct.hddTime;
    DEBUG("The int is " << m_configStruct.hddTime);
    return true;
  }

  bool Parser::perform_PrinterState()
  {
     std::string input;
    // Skip next three words
    m_inf >> input;
    m_inf >> input;
    m_inf >> input;

    // Last is an int
    m_inf >> m_configStruct.printerTime;
    DEBUG("The int is " << m_configStruct.printerTime);
    return true;
  }

  bool Parser::perform_KeyboardState()
  {
    std::string input;
    // Skip next three words
    m_inf >> input;
    m_inf >> input;
    m_inf >> input;

    // Last is an int
    m_inf >> m_configStruct.keyboardTime;
    DEBUG("The int is " << m_configStruct.keyboardTime);
    return true;
  }

  bool Parser::perform_MemoryState()
  {
    std::string input;
    // Skip next three words
    m_inf >> input;
    m_inf >> input;
    m_inf >> input;

    // Last is an int
    m_inf >> m_configStruct.memoryTime;
    DEBUG("The int is " << m_configStruct.memoryTime);
    return true;
  }

  bool Parser::perform_MouseState()
  {
    std::string input;
    // Skip next three words
    m_inf >> input;
    m_inf >> input;
    m_inf >> input;

    // Last is an int
    m_inf >> m_configStruct.mouseTime;
    DEBUG("The int is " << m_configStruct.mouseTime);
    return true;
  }

  bool Parser::perform_SpeakerState()
  {
    std::string input;
    // Skip next three words
    m_inf >> input;
    m_inf >> input;
    m_inf >> input;

    // Last is an int
    m_inf >> m_configStruct.speakerTime;
    DEBUG("The int is " << m_configStruct.speakerTime);
    return true;
  }

  bool Parser::perform_MetaPathState()
  {
     DEBUG("");
  }

  bool Parser::perform_LogStyleState()
  {
    std::string input;
    // Skip next two words
    m_inf >> input;
    m_inf >> input;

    // Last word tells us how to log
    m_inf >> input;
    if(input == "Both")
      m_configStruct.logStyle = m_configStruct.LogStyle::LogToBoth;
    else if(input == "File")
      m_configStruct.logStyle = m_configStruct.LogStyle::LogToFile;
    else
      m_configStruct.logStyle = m_configStruct.LogStyle::LogToMonitor;

     DEBUG("The log style is " << input);
     return true;
  }

  bool Parser::perform_LogPathState()
  {
    std::string input;
    // skip next two words
    m_inf >> input;
    m_inf >> input;

    // last word is the file path
    m_inf >> input;
    std::string extension = substr_from_delim(input, '.');
    if(extension != "out")
    {
      m_errorString += "\n* The extension " + extension + " is not supported as an output file."
                    +  " The extension must be out. The filepath supplied is " + input;
      return false;
    }

    m_configStruct.logPath = input;
     DEBUG("");
     return true;
  }

  bool Parser::perform_SkipState(std::string skippedWord)
  {
     DEBUG(skippedWord);
  }

  bool Parser::parse_meta()
  {
	  // Open file, throw error if unable to open
	  m_inf.open(m_configStruct.metafile.c_str());
	  if(not m_inf.good())
	  {
		  m_errorString += "The metafile " + m_configStruct.metafile + " could not be opened? Does it exist?";
		  return false;
	  }


	  // Hackish solution until I write something better (if ever c:)
	  std::string inputString;
	  m_inf >> inputString;
	  m_inf >> inputString;
	  m_inf >> inputString;
	  m_inf >> inputString;

	  bool successfulInstruction = true;
	  while(successfulInstruction and m_inf.good())
	  {
		  //succssfulInstruction = check_valid_syntax(inputString);
		  inputString = extract_instruction();
		  if(inputString == "\n" or inputString == "")
			  continue;



		  DEBUG("The instruction extracted is " << inputString);
	  }

	  return true;
  }

  std::string Parser::extract_instruction()
  {
	  std::string instructionString = "";

	  // Loop until a valid delimiter is reached
	  char c;
	  m_inf >> std::noskipws >> c;
	  while(m_inf.good() and c != ';' and c != ':' and c != ',' and c != '\n' and c != '.' and c != '!')
	  {
		  instructionString += c;
		  m_inf >> std::noskipws >> c;
	  }

	  //instructionString += c;

	  instructionString.erase(std::remove(instructionString.begin(), instructionString.end(), ' '), instructionString.end());
	  return instructionString;
  }

  bool Parser::check_valid_syntax(std::string instructionString, Instruction & instructionStruct)
  {
	  std::string instructionCode, instructionDesc, instructionTime;

	  instructionCode = substr_to_delim(instructionString, '(');
	  instructionDesc = substr_to_from_delim(instructionString, '(', ')');
	  instructionTime = substr_from_delim(instructionString, ')');


  }

}
