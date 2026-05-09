import strutils

proc formatArticle*(article: string): string =
  var title = "Unknown title"
  var actionNeeded = "unknown"
  var articleContent: string
  var inContent = false

  for line in article.splitLines():
    if line.startsWith("TITLE:"):
      title = line.split(":")[1].strip()
      continue
    if line.startsWith("ACTION-NEEDED:"):
      actionNeeded = line.split(":")[1].strip()
      continue
    
    if (line == ";") and (not inContent):
      inContent = true
      continue
    if (line == ";") and (inContent):
      inContent = false
      continue
    if inContent:
      articleContent &= "\n" & line

  actionNeeded = if actionNeeded == "false":
                     "(\e[92mno action needed\e[0m)"
                   elif actionNeeded == "true":
                     "(\e[91maction required\e[0m)"
                   else:
                    ""

  result = "\e[94;1m>\e[0m \e[1m" & title & "\e[0m " & actionNeeded
  result &= "\e[3m" & articleContent & "\e[0m"