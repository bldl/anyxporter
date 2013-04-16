local function xml_esc (s)
  s = string.gsub(s, "<", "&lt;")
  s = string.gsub(s, ">", "&gt;")
  s = string.gsub(s, "&", "&amp;")
  return s
end

preamble_string = [[<?xml version="1.0" encoding="UTF-8"?>
<contacts>
]]

postamble_string = "</contacts>\n"

local function f (n, e)
  return string.format("    <%s>%s</%s>\n", n, xml_esc(e[n]), n)
end

function entry_to_string (e)
  return "  <contact>\n" ..
    f("first_name", e) ..
    f("last_name", e) ..
    "  </contact>\n"
end
