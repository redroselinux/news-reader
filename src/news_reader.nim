import os

import fetch

when isMainModule:
  let argv = commandLineParams()
  let argc = len(argv)

  if argc == 0:
    fetchLatest()
  else:
    if argv[0] == "help":
      echo "news-reader v0.1"
      echo "read the latest redrose linux news"
      echo ""
      echo "usage: news-reader [command] [args]"
      echo ""
      echo "commands:"
      echo "  (no args)           fetch and read latest"
      echo "  read <date>         fetch and read a specific article"
      echo "  mark read <id>      mark as read (latest or <date>)"
      echo "  mark unread <id>    mark as unread (latest or <date>)"
      echo "  help                show this help message"
      echo ""
      echo "examples:"
      echo "  news-reader read 2026(09.04)"
      echo "  news-reader mark read latest"
    elif argv[0] == "read":
      if argc == 1:
        echo "\e[91m*\e[0m You must specify the article to read"
        echo "\e[93m*\e[0m Run 'news-reader help'"
    else:
      echo "\e[91m*\e[0m Unknown command"