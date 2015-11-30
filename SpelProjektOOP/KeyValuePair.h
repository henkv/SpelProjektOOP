#pragma once

template<typename KeyT, typename ValueT>
class KeyValuePair
{
	private:
	KeyT key;
	ValueT value;

	public:
	KeyValuePair(KeyT key, ValueT value)
	{
		this->key = key;
		this->value = value;
	}
	~KeyValuePair() {}

	KeyT& getKey()
	{
		return key;
	}
	ValueT& getValue()
	{
		return value;
	}

	void setKey(KeyT key)
	{
		this->key = key;
	}
	void setValue(ValueT value)
	{
		this->value = value;
	}

	bool operator==(const KeyValuePair& kvp) const
	{
		return key == kvp.key;
	}
	bool operator<(const KeyValuePair& kvp) const
	{
		return key < kvp.key;
	}
	bool operator>(const KeyValuePair& kvp) const
	{
		return key > kvp.key;
	}	
};

