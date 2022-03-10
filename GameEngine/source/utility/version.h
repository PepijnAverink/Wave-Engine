#pragma once
#include <stdint.h>

class Version
{
public:
	Version() = default;
	Version(const uint32_t _versionID)
		: m_VersionID(_versionID)
	{ }
	Version(const uint8_t _major, const uint8_t _minor, const uint8_t _patch, const uint8_t _tweak)
		: m_Major(_major)
		, m_Minor(_minor)
		, m_Patch(_patch)
		, m_Tweak(_tweak)
	{ }

	// Getters
	inline uint32_t GetVersionID() const { return m_VersionID; }

	inline uint8_t GetMajorVersion() const { return m_Major; }
	inline uint8_t GetMinorVersion() const { return m_Minor; }
	inline uint8_t GetPatchVersion() const { return m_Patch; }
	inline uint8_t GetTweakVersion() const { return m_Tweak; }

private:
	union
	{
		uint32_t m_VersionID;
		struct { uint8_t m_Major; uint8_t m_Minor; uint8_t m_Patch; uint8_t m_Tweak; };
	};
};