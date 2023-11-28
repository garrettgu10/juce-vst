/* ==================================== JUCER_BINARY_RESOURCE ====================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#include <cstring>

namespace BinaryData
{

//================== magic.xml ==================
static const unsigned char temp_binary_data_0[] =
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n"
"\r\n"
"<magic>\r\n"
"  <Styles>\r\n"
"    <Style name=\"default\">\r\n"
"      <Nodes/>\r\n"
"      <Classes>\r\n"
"        <plot-view border=\"2\" background-color=\"black\" border-color=\"silver\" display=\"contents\"/>\r\n"
"        <nomargin margin=\"0\" padding=\"0\" border=\"0\"/>\r\n"
"        <group margin=\"5\" padding=\"5\" border=\"2\" flex-direction=\"column\"/>\r\n"
"        <transparent background-color=\"transparentblack\"/>\r\n"
"      </Classes>\r\n"
"      <Types>\r\n"
"        <Slider border=\"0\" slider-textbox=\"textbox-below\"/>\r\n"
"        <ToggleButton border=\"0\" max-height=\"50\" caption-size=\"0\" text=\"Active\"/>\r\n"
"        <TextButton border=\"0\" max-height=\"50\" caption-size=\"0\"/>\r\n"
"        <ComboBox border=\"0\" max-height=\"50\" caption-size=\"0\"/>\r\n"
"        <Plot border=\"0\" margin=\"0\" padding=\"0\" background-color=\"00000000\"\r\n"
"              radius=\"0\"/>\r\n"
"        <XYDragComponent border=\"0\" margin=\"0\" padding=\"0\" background-color=\"00000000\"\r\n"
"                         radius=\"0\"/>\r\n"
"      </Types>\r\n"
"      <Palettes>\r\n"
"        <default/>\r\n"
"      </Palettes>\r\n"
"    </Style>\r\n"
"  </Styles>\r\n"
"  <View id=\"root\" resizable=\"1\" resize-corner=\"1\">\r\n"
"    <View class=\"parameters nomargin\" flex-direction=\"column\">\r\n"
"      <Label text=\"disgusting repitch\" justification=\"centred\" font-size=\"25\"\r\n"
"             height=\"\" pos-x=\"0%\" pos-y=\"0%\" pos-width=\"100%\" pos-height=\"33.3333%\"/>\r\n"
"      <TextButton pos-x=\"0%\" pos-y=\"50%\" pos-width=\"100%\" pos-height=\"50%\" onClick=\"loadFile\"\r\n"
"                  text=\"Load File\"/>\r\n"
"      <View>\r\n"
"        <Slider parameter=\"knob1\"/>\r\n"
"        <Label text=\"playback speed\"/>\r\n"
"      </View>\r\n"
"    </View>\r\n"
"  </View>\r\n"
"</magic>\r\n";

const char* magic_xml = (const char*) temp_binary_data_0;


const char* getNamedResource (const char* resourceNameUTF8, int& numBytes);
const char* getNamedResource (const char* resourceNameUTF8, int& numBytes)
{
    unsigned int hash = 0;

    if (resourceNameUTF8 != nullptr)
        while (*resourceNameUTF8 != 0)
            hash = 31 * hash + (unsigned int) *resourceNameUTF8++;

    switch (hash)
    {
        case 0x7ee40a85:  numBytes = 1610; return magic_xml;
        default: break;
    }

    numBytes = 0;
    return nullptr;
}

const char* namedResourceList[] =
{
    "magic_xml"
};

const char* originalFilenames[] =
{
    "magic.xml"
};

const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8)
{
    for (unsigned int i = 0; i < (sizeof (namedResourceList) / sizeof (namedResourceList[0])); ++i)
        if (strcmp (namedResourceList[i], resourceNameUTF8) == 0)
            return originalFilenames[i];

    return nullptr;
}

}
