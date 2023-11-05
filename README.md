# USAGE:
  This is a lexer to recognize c language tokens.
  
  Entrance function is :
  
    ``bool LEXER_EXPORT ParseFile(const char* fileName, Token* tokens, unsigned maxToken);``
    
  Given src path, token buffer and capacity, It will parse the .c file and store tokens at the buffer.
  If parsed without error, it will return true. Otherwise it returns false.