{
  "variables": {
    "openssl_fips" : "0"
  },
  "targets": [
    {
      "target_name": "iselevated",
      "sources": [
        "src/iselevated.cc"
      ],
      "cflags": [
        "-O2",
        "-fstack-protector-strong",
      ],
      "msvs_configuration_attributes": {
        "SpectreMitigation": "Spectre"
      },
      "msvs_settings": {
        "VCCLCompilerTool": {
          "AdditionalOptions": [
            "/guard:cf",
            "/sdl",
            "/W3",
            "/we4146",
            "/we4244",
            "/we4267",
            "/ZH:SHA_256"
          ]
        },
        "VCLinkerTool": {
          "AdditionalOptions": [
            "/DYNAMICBASE",
            "/guard:cf"
          ]
        }
      }
    }
  ]
}
