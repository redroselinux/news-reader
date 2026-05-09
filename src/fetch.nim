import osproc
import strutils

import format_article

proc fetchLatest*(): int =
  var p = startProcess(
    "curl",
    args = [
      "-s", "-L", "-o", "/tmp/news-reader-latest",
      "https://github.com/redroselinux/news-reader/" &
      "raw/refs/heads/master/news/latest"
    ],
    options = {poUsePath}
  )

  if p.waitForExit() != 0:
    p.close()
    echo "\e[91m*\e[0m Failed to fetch latest news"
    return 1
  p.close()

  var latest: string
  try:
    latest = readFile("/tmp/news-reader-latest").strip()
  except:
    echo "\e[91m*\e[0m Failed to read latest news"
    return 1

  # latest is simply a url; fetch the url we just got
  p = startProcess(
    "curl",
    args = ["-s", "-L", "-o", "/tmp/news-reader-latest", latest],
    options = {poUsePath}
  )

  if p.waitForExit() != 0:
    p.close()
    echo "\e[91m*\e[0m Failed to fetch latest news"
    return 1
  p.close()

  try:
    latest = readFile("/tmp/news-reader-latest")
  except:
    echo "\e[91m*\e[0m Failed to read latest news"
    return 1
  if latest.strip.startsWith("<!DOCTYPE html>"):
    echo "\e[91m*\e[0m Failed to fetch latest"
    return 1
  
  echo formatArticle(latest)
  return 0

proc fetchSpecific*(date: string): int =
  var p = startProcess(
    "curl",
    args = [
      "-s", "-L", "-o", "/tmp/news-reader-latest",
      "https://github.com/redroselinux/news-reader/" &
      "raw/refs/heads/master/news/" & date
    ],
    options = {poUsePath}
  )

  if p.waitForExit() != 0:
    p.close()
    echo "\e[91m*\e[0m Failed to fetch article " & date
    return 1
  p.close()

  var latest: string
  try:
    latest = readFile("/tmp/news-reader-latest")
  except:
    echo "\e[91m*\e[0m Failed to read " & date
    return 1
  if latest.strip.startsWith("<!DOCTYPE html>"):
    echo "\e[91m*\e[0m Failed to fetch " & date
    return 1

  echo formatArticle(latest)
  return 0