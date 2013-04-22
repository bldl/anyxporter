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

local function table_size (t)
  local n = 0
  for _, _ in pairs(t) do
    n = n + 1
  end
  return n
end

--print(table_size({1, 3, 5}))

local function is_array (x)
  if type(x) ~= "table" then return nil end
  local n = table_size(x)
  local ni = 0
  for _, _ in ipairs(x) do
    ni = ni + 1
  end
  return n == ni
end

--print(is_array(true))
--print(is_array({1, 3, 5}))
--print(is_array({1, 3, a = 5}))

preamble_string = [[<?xml version="1.0" encoding="UTF-8"?><Contacts>]]

postamble_string = [[</Contacts>]]

local function datum_to_string (e)
  if type(e) == "string" then
    return xml_esc(e)
  elseif type(e) == "table" then
    if is_array(e) then
      local s = ""
      for _, v in ipairs(e) do
	s = s .. string.format([[<element>%s</element>]], v)
      end
      return s
    else
      local s = ""
      local ks = table_keys(e)
      for i, k in ipairs(ks) do
	s = s .. string.format([[<%s>%s</%s>]], k, datum_to_string(e[k]), k)
      end
      return s
    end
  else
    error("unsupported type " + type(e))
  end
end

local function details_to_string (ds)
  local s = ""
  table.sort(ds, function (x, y)
		   return x["DefinitionName"] < y["DefinitionName"]
		 end)
  for k, v in ipairs(ds) do
    s = s .. [[<ContactDetail>]] .. 
      datum_to_string(v) .. [[</ContactDetail>]]
  end
  return s
end

function entry_to_string (e)
  local s = [[<Contact>]]
  s = s .. details_to_string(e)
  s = s .. [[</Contact>]]
  return s
end
