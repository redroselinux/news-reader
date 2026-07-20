# `news-reader`

A CLI tool to read the latest Redrose Linux news, written in C.

Full docs: https://docs.redroselinux.org/#/news-reader

## Installation

If your Redrose system somehow does not have it installed:

```
sudo car install news-reader
```

## `news/` structure

- `latest` - a file with just the url to the latest article
- `YYYY(DD.MM)` - articles, example:
  ```
  TITLE: Alpha-0.5.1 coming soon
  ACTION-NEEDED: false
  
  ;
  alpha-0.5.1 will be released soon-ish. It introduces a lot of bugfixes:
  - car was broken
  - ncurses was broken (at the time of saying this, still being fixed)
  - FINALLY, finally we do not use the defconfig kernel
  ;
  ```
