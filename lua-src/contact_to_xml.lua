local function xml_esc (s)
  s = string.gsub(s, "<", "&lt;")
  s = string.gsub(s, ">", "&gt;")
  s = string.gsub(s, "&", "&amp;")
  return s
end

local function table_keys (t)
  local keyset = {}
  local n = 0
  for k in pairs(t) do
    n = n + 1
    keyset[n] = k
  end
  table.sort(keyset)
  return keyset
end

--for k, v in ipairs(table_keys({a = 1, b = 2})) do 
--  print(v)
--end

preamble_string = [[<?xml version="1.0" encoding="UTF-8"?>
<contacts>
]]

postamble_string = "</contacts>\n"

local function f (n, e)
  return string.format("    <%s>%s</%s>\n", n, xml_esc(e[n]), n)
end

function entry_to_string (e)
  local ks = table_keys(e)
  local s = "  <contact>\n"
  for k, v in ipairs(ks) do
    s = s .. f(v, e)
  end
  s = s .. "  </contact>\n"
  return s
end
