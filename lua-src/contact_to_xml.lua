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

--for k, v in ipairs(table_keys({a = 1, b = 2})) do print(v) end

preamble_string = [[<?xml version="1.0" encoding="UTF-8"?><contacts>]]

postamble_string = [[</contacts>]]

local function datum_to_string (e)
  if type(e) == "string" then
    return xml_esc(e)
  elseif type(e) == "table" then
    local s = ""
    local ks = table_keys(e)
    for i, k in ipairs(ks) do
      s = s .. string.format([[<%s>%s</%s>]], k, datum_to_string(e[k]), k)
    end
    return s
  else
    error("unsupported type " + type(e))
  end
end

function entry_to_string (e)
  local s = [[<contact>]]
  s = s .. datum_to_string(e)
  s = s .. [[</contact>]]
  return s
end
